# routes/index.py
from flask import Blueprint, render_template, session, redirect, url_for

index_bp = Blueprint('index', __name__)

# 홈 화면
@index_bp.route('/')
def index():
    return render_template('index.html', user=session.get('user'))

# 로그아웃 처리
@index_bp.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('index.index'))
