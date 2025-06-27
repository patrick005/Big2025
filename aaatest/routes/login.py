# routes/login.py
from flask import Blueprint, render_template, request, redirect, session, url_for, flash
import bcrypt
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
            return redirect(url_for('upload.upload'))
        else:
            flash("아이디 또는 비밀번호가 올바르지 않습니다.")
            return redirect(url_for('login.login_page'))

    return render_template('login.html')