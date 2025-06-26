# routes/login.py
from flask import Blueprint, render_template, request, redirect, session, url_for, flash
import bcrypt
import os, requests
from models import db, User

login_bp = Blueprint('login', __name__)

@login_bp.route('/login', methods=['GET', 'POST'])
def login_page():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        user = User.query.filter_by(username=username).first()
        if user and bcrypt.checkpw(password.encode('utf-8'), user.password.encode('utf-8')):
            session.permanent = True
            session['user'] = {'id': user.id, 'nickname': user.name}
            flash("로그인 성공!")
            return redirect(url_for('upload.upload'))
        else:
            flash("아이디 또는 비밀번호가 올바르지 않습니다.")
            return redirect(url_for('login.login_page'))

    return render_template('login.html')

@login_bp.route('/login/kakao')
def login_kakao():
    session['auth_type'] = 'login'
    kakao_rest_api_key = os.environ.get('KAKAO_REST_KEY', '372b9ff0b3185bf66106edc076409718')
    redirect_uri = url_for('login.oauth', _external=True)

    return redirect(
        f"https://kauth.kakao.com/oauth/authorize?"
        f"client_id={kakao_rest_api_key}&redirect_uri={redirect_uri}&response_type=code"
    )

@login_bp.route('/signup/kakao')
def signup_kakao():
    session['auth_type'] = 'signup'
    return redirect(url_for('login.login_kakao'))

@login_bp.route('/oauth')
def oauth():
    code = request.args.get('code')
    if not code:
        return "인증 코드가 없습니다", 400

    kakao_rest_api_key = os.environ.get('KAKAO_REST_KEY', '372b9ff0b3185bf66106edc076409718')
    token_url = 'https://kauth.kakao.com/oauth/token'
    redirect_uri = url_for('login.oauth', _external=True)
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
    nickname = user_info['properties']['nickname']

    user = User.query.filter_by(kakao_id=kakao_id).first()
    if not user:
        user = User(kakao_id=kakao_id, nickname=nickname)
        db.session.add(user)
        db.session.commit()

    session.permanent = True
    session['user'] = {'id': user.id, 'nickname': user.nickname}
    return redirect(url_for('upload.upload'))