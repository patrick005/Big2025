# routes/reset.py
from flask import Blueprint, render_template, request, redirect, session, url_for, flash
from models import db, User
import random, smtplib, os, re
from email.mime.text import MIMEText
import bcrypt

reset_bp = Blueprint('reset', __name__)

@reset_bp.route('/reset', methods=['GET', 'POST'])
def reset_request():
    if request.method == 'POST':
        username = request.form.get('username')
        name = request.form.get('name')
        email = request.form.get('email')

        user = User.query.filter_by(username=username, name=name, email=email).first()
        if not user:
            flash("일치하는 사용자가 없습니다.")
            return redirect(url_for('reset.reset_request'))

        code = str(random.randint(100000, 999999))
        session['reset_code'] = code
        session['reset_user'] = user.id
        session['reset_email'] = email  # 추가됨

        if send_code_to_email(email, code):
            flash("인증 코드가 이메일로 전송되었습니다.")
        else:
            flash("이메일 전송 중 문제가 발생했습니다.")

        return redirect(url_for('reset.reset_verify'))

    return render_template('reset_request.html')

@reset_bp.route('/reset/verify', methods=['GET', 'POST'])
def reset_verify():
    if request.method == 'POST':
        code = request.form.get('code')
        if code == session.get('reset_code'):
            session['reset_verified'] = True
            return redirect(url_for('reset.reset_password'))
        else:
            flash("인증 코드가 올바르지 않습니다.")
            return redirect(url_for('reset.reset_verify'))

    return render_template('reset_verify.html')

@reset_bp.route('/reset/password', methods=['GET', 'POST'])
def reset_password():
    if not session.get('reset_verified') or 'reset_user' not in session:
        flash("인증 절차를 완료해주세요.")
        return redirect(url_for('reset.reset_request'))

    if request.method == 'POST':
        new_password = request.form.get('new_password')

        # 비밀번호 유효성 검사
        if len(new_password) < 8 or not re.search(r'[!@#$%^&*(),.?":{}|<>]', new_password):
            flash("비밀번호는 8자 이상이며, 최소 1개의 특수문자를 포함해야 합니다.")
            return redirect(url_for('reset.reset_password'))

        hashed_pw = bcrypt.hashpw(new_password.encode('utf-8'), bcrypt.gensalt()).decode('utf-8')

        user = User.query.get(session['reset_user'])
        user.password = hashed_pw
        db.session.commit()

        session.pop('reset_code', None)
        session.pop('reset_user', None)
        session.pop('reset_verified', None)
        session.pop('reset_email', None)
        flash("비밀번호가 성공적으로 변경되었습니다.")
        return redirect(url_for('login.login_page'))

    return render_template('reset_password.html')

def send_code_to_email(email, code):
    try:
        smtp_user = os.environ.get('EMAIL_USER')
        smtp_pass = os.environ.get('EMAIL_PASS')

        if not smtp_user or not smtp_pass:
            print("환경변수 EMAIL_USER 또는 EMAIL_PASS가 비어있습니다.")
            return False

        msg = MIMEText(f"인증코드는 다음과 같습니다: {code}")
        msg['Subject'] = "비밀번호 재설정 인증코드"
        msg['From'] = smtp_user
        msg['To'] = email

        server = smtplib.SMTP('smtp.naver.com', 587)
        server.ehlo()
        server.starttls()
        server.login(smtp_user, smtp_pass)
        server.send_message(msg)
        server.quit()
        return True
    except Exception as e:
        print("이메일 전송 실패:", e)
        return False
