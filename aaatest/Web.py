# Web.py
from flask import Flask
from models import db, User
from routes import (
    index_bp, login_bp, signup_bp,
    upload_bp, recommend_bp, result_bp,
    oauth_bp, reset_bp
)
import os
from datetime import timedelta
from sqlalchemy import inspect
from dotenv import load_dotenv

# .env 파일 불러오기
load_dotenv()

app = Flask(__name__)
app.secret_key = os.environ.get('SECRET_KEY', 'your_secret_key')

# 경로 설정
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
db_path = os.path.join(BASE_DIR, 'mmm.db')
app.config['UPLOAD_FOLDER'] = os.path.join(BASE_DIR, 'static/uploads/')
app.config['SQLALCHEMY_DATABASE_URI'] = f'sqlite:///{db_path}'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.permanent_session_lifetime = timedelta(minutes=5)

# DB 초기화
db.init_app(app)
os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)

# DB 테이블 생성
with app.app_context():
    db.create_all()
    inspector = inspect(db.engine)
    print("✅ DB 테이블 생성/확인 완료:", inspector.get_table_names())

print("EMAIL_USER:", os.environ.get("EMAIL_USER"))
print("EMAIL_PASS:", os.environ.get("EMAIL_PASS"))

    
# Blueprint 등록
app.register_blueprint(index_bp)
app.register_blueprint(login_bp)
app.register_blueprint(signup_bp)
app.register_blueprint(upload_bp)
app.register_blueprint(recommend_bp)
app.register_blueprint(result_bp)
app.register_blueprint(oauth_bp)
app.register_blueprint(reset_bp)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080, debug=True)
