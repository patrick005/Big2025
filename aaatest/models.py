from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)

    # 카카오 로그인 전용
    kakao_id = db.Column(db.String(128), unique=True, nullable=True)

    # 전통 로그인 전용
    username = db.Column(db.String(64), unique=True, nullable=True)
    password = db.Column(db.String(255), nullable=True)

    # 공통
    name = db.Column(db.String(64), nullable=True)         # 실명 또는 기본 이름
    email = db.Column(db.String(128), unique=True, nullable=True)  # 카카오 또는 직접 입력 이메일
    nickname = db.Column(db.String(64), nullable=True)     # 카카오 닉네임 또는 별칭