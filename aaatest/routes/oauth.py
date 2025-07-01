import os
from flask import Blueprint, redirect, request, session, url_for, flash, render_template
import requests
from models import db, User

oauth_bp = Blueprint('oauth', __name__)

@oauth_bp.route('/login/kakao')
def login_kakao():
    session['auth_type'] = 'login'
    kakao_rest_api_key = os.environ.get('KAKAO_REST_KEY', 'your_default_key')
    redirect_uri = url_for('oauth.oauth', _external=True)
    return redirect(
        f"https://kauth.kakao.com/oauth/authorize"
        f"?client_id={kakao_rest_api_key}"
        f"&redirect_uri={redirect_uri}"
        f"&response_type=code"
        f"&prompt=login"
    )

@oauth_bp.route('/signup/kakao')
def signup_kakao():
    session['auth_type'] = 'signup'
    return redirect(url_for('oauth.login_kakao'))

@oauth_bp.route('/oauth')
def oauth():
    code = request.args.get('code')
    if not code:
        return "인증 코드가 없습니다.", 400

    kakao_rest_api_key = os.environ.get('KAKAO_REST_KEY', 'your_default_key')
    redirect_uri = url_for('oauth.oauth', _external=True)
    token_response = requests.post(
        'https://kauth.kakao.com/oauth/token',
        data={
            'grant_type': 'authorization_code',
            'client_id': kakao_rest_api_key,
            'redirect_uri': redirect_uri,
            'code': code
        },
        headers={'Content-type': 'application/x-www-form-urlencoded;charset=utf-8'}
    )
    token_json = token_response.json()
    if 'access_token' not in token_json:
        return f"토큰 요청 실패: {token_json.get('error_description', token_json)}", 400

    access_token = token_json['access_token']
    user_info = requests.get(
        'https://kapi.kakao.com/v2/user/me',
        headers={'Authorization': f'Bearer {access_token}'}
    ).json()

    kakao_id = str(user_info.get('id'))
    properties = user_info.get('properties', {})
    account = user_info.get('kakao_account', {})
    profile = account.get('profile', {})

    nickname = properties.get('nickname') or profile.get('nickname', f"사용자_{kakao_id}")
    email = account.get('email', f"{kakao_id}@kakao.com")
    name = profile.get('nickname', nickname)

    user = User.query.filter_by(kakao_id=kakao_id).first()
    auth_type = session.get('auth_type')

    if auth_type == 'signup':
        if user:
            # 이미 가입된 경우 로그인 상태로 index로
            session.permanent = True
            session['user'] = {'id': user.id, 'nickname': user.nickname}
            flash("이미 가입된 카카오 계정으로 로그인되었습니다.")
            return redirect(url_for('index.index'))  # index.html 렌더링하는 라우트 이름에 맞추세요
        else:
            # 신규 가입 처리
            user = User(kakao_id=kakao_id, name=name, nickname=nickname, email=email)
            db.session.add(user)
            db.session.commit()
            session.permanent = True
            session['user'] = {'id': user.id, 'nickname': user.nickname}
            flash("카카오 계정으로 회원가입이 완료되었습니다.")
            return redirect(url_for('index.index'))

    elif auth_type == 'login':
        if not user:
            flash("등록되지 않은 카카오 계정입니다. 먼저 회원가입 해주세요.")
            return redirect(url_for('signup.signup_page'))
        else:
            session.permanent = True
            session['user'] = {'id': user.id, 'nickname': user.nickname}
            flash("카카오 계정으로 로그인되었습니다.")
            return redirect(url_for('index.index'))

    else:
        return "잘못된 접근입니다. 로그인 또는 회원가입을 선택해주세요.", 400