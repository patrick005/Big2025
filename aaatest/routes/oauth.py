# routes/oauth.py
import os
from flask import Blueprint, redirect, request, session, url_for
import requests
from models import db, User

oauth_bp = Blueprint('oauth', __name__)

@oauth_bp.route('/login/kakao')
def login_kakao():
    session['auth_type'] = 'login'
    kakao_rest_api_key = os.environ.get('KAKAO_REST_KEY', 'your_default_key')
    redirect_uri = url_for('oauth.oauth', _external=True)
    return redirect(
        f"https://kauth.kakao.com/oauth/authorize?"
        f"client_id={kakao_rest_api_key}&redirect_uri={redirect_uri}&response_type=code"
    )

@oauth_bp.route('/signup/kakao')
def signup_kakao():
    session['auth_type'] = 'signup'
    return redirect(url_for('oauth.login_kakao'))

@oauth_bp.route('/oauth')
def oauth():
    code = request.args.get('code')
    if not code:
        return "인증 코드가 없습니다", 400

    kakao_rest_api_key = os.environ.get('KAKAO_REST_KEY', 'your_default_key')
    token_url = 'https://kauth.kakao.com/oauth/token'
    redirect_uri = url_for('oauth.oauth', _external=True)
    payload = {
        'grant_type': 'authorization_code',
        'client_id': kakao_rest_api_key,
        'redirect_uri': redirect_uri,
        'code': code
    }
    headers = {'Content-type': 'application/x-www-form-urlencoded;charset=utf-8'}
    token_response = requests.post(token_url, data=payload, headers=headers)
    token_json = token_response.json()
    if 'access_token' not in token_json:
        error_desc = token_json.get('error_description', str(token_json))
        return f"토큰 요청 실패: {error_desc}", 400

    access_token = token_json['access_token']
    user_info_response = requests.get(
        'https://kapi.kakao.com/v2/user/me',
        headers={'Authorization': f'Bearer {access_token}'}
    )
    user_info = user_info_response.json()
    kakao_id = str(user_info['id'])
    email = user_info.get('kakao_account', {}).get('email', f"{kakao_id}@kakao.com")
    name = user_info.get('properties', {}).get('nickname', f"사용자_{kakao_id}")

    user = User.query.filter_by(kakao_id=kakao_id).first()
    if not user:
        user = User(kakao_id=kakao_id, name=name, email=email)
        db.session.add(user)
        db.session.commit()

    session.permanent = True
    session['user'] = {'id': user.id, 'nickname': name}
    return redirect(url_for('upload.upload'))
