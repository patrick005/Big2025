# routes/signup.py
from flask import Blueprint, render_template, request, redirect, session, url_for, flash
import bcrypt
import re
from models import db, User

signup_bp = Blueprint('signup', __name__)

@signup_bp.route('/signup', methods=['GET', 'POST'])
def signup_page():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        name = request.form['name']
        email = request.form['email']

        if not (4 <= len(username) <= 12):
            flash("아이디는 4자 이상 12자 이하여야 합니다.")
            return redirect(url_for('signup.signup_page'))

        if len(password) < 8 or not re.search(r'[!@#$%^&*(),.?":{}|<>]', password):
            flash("비밀번호는 8자 이상이면서 특수문자를 포함해야 합니다.")
            return render_template('signup.html')

        if User.query.filter_by(username=username).first():
            flash("이미 존재하는 아이디입니다.")
            return redirect(url_for('signup.signup_page'))

        if User.query.filter_by(email=email).first():
            flash("이미 가입된 이메일입니다.")
            return redirect(url_for('signup.signup_page'))

        hashed_pw = bcrypt.hashpw(password.encode('utf-8'), bcrypt.gensalt()).decode('utf-8')
        user = User(username=username, password=hashed_pw, name=name, email=email)
        db.session.add(user)
        db.session.commit()

        session.permanent = True
        session['user'] = {'id': user.id, 'nickname': name}
        flash("회원가입이 완료되었습니다.")
        return redirect(url_for('upload.upload'))

    return render_template('signup.html')

@signup_bp.route('/check_username')
def check_username():
    username = request.args.get('username')
    exists = User.query.filter_by(username=username).first() is not None
    return {'available': not exists}
