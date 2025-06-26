# routes/result.py
from flask import Blueprint, render_template, redirect, session, url_for, request
import time, requests

result_bp = Blueprint('result', __name__)

# POST 방식으로 옷 선택 시 로딩 화면으로 이동
@result_bp.route('/dress', methods=['POST'])
def dress_post():
    if 'user' not in session:
        return redirect(url_for('index.index'))

    selected_item = request.form.get('clothes_img')
    if not selected_item:
        return "옷이 선택되지 않았습니다", 400

    session['selected_item'] = selected_item
    session['loading_stage'] = '가상 피팅'
    return redirect(url_for('result.loading'))

# 로딩 화면 표시 (Colab 호출 전 단계)
@result_bp.route('/dress/loading')
def loading():
    if 'user' not in session:
        return redirect(url_for('index.index'))

    stage = session.get('loading_stage', '처리')
    return render_template('loading.html', stage=stage)

# Colab 호출 및 결과 페이지로 리디렉션
@result_bp.route('/dress/process')
def process():
    if 'user' not in session:
        return redirect(url_for('index.index'))

    photo_path = session.get('photo_path')
    selected_item = session.get('selected_item')
    if not photo_path or not selected_item:
        return redirect(url_for('upload.upload'))

    # ⏳ Colab 서버에 POST 요청 (예시 URL, 실제 사용 시 바꿔야 함)
    try:
        response = requests.post(
            'https://your-colab-link.com/fit',
            json={'photo_path': photo_path, 'clothes_img': selected_item},
            timeout=60
        )
        result_url = response.json().get('result_url', photo_path)
    except Exception as e:
        print("Colab 호출 실패:", e)
        result_url = photo_path

    return redirect(url_for('result.result', item=selected_item, result=result_url))

# 최종 결과 페이지
@result_bp.route('/dress/<path:item>')
def result(item):
    if 'user' not in session:
        return redirect(url_for('index.index'))

    result_url = request.args.get('result') or session.get('photo_path')

    return render_template(
        'result.html',
        result=result_url,
        item=item,
        user=session.get('user'),
        previous=url_for('recommend.recommend')
    )
