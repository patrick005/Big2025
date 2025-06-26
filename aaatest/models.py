from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    kakao_id = db.Column(db.String(128), unique=True, nullable=True)   # 카카오 로그인 전용 ID
    username = db.Column(db.String(64), unique=True, nullable=True)    # 일반 회원가입용 ID
    password = db.Column(db.String(255), nullable=True)                # bcrypt 해싱된 비밀번호
    name = db.Column(db.String(64), nullable=False)                    # 이름 (필수)
    email = db.Column(db.String(120), unique=True, nullable=False)     # 이메일 (인증/비밀번호 재설정용)
