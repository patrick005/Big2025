# routes/recommend.py
from flask import Blueprint, render_template, session, redirect, url_for

recommend_bp = Blueprint('recommend', __name__)

@recommend_bp.route('/recommend')
def recommend():
    if 'user' not in session:
        return redirect(url_for('index.index'))

    photo_path = session.get('photo_path')
    if not photo_path:
        return redirect(url_for('upload.upload'))

    # DB 없이 직접 아이템 정보 정의
    items = [
        {"name": "블레이저", "image": "/static/clothes/blazer.png"},
        {"name": "셔츠", "image": "/static/clothes/shirt.png"},
        {"name": "가디간", "image": "/static/clothes/cardigan.png"}
    ]

    return render_template('recommend.html',
                           photo=photo_path,
                           items=items,
                           user=session.get('user'))
