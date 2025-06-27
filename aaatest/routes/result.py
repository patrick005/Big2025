from flask import Blueprint, render_template, redirect, session, url_for, request, flash

result_bp = Blueprint('result', __name__)

@result_bp.route('/dress', methods=['POST'])
def dress_post():
    if 'user' not in session:
        flash("로그인 후 이용해주세요.")
        return redirect(url_for('login.login_page'))

    selected_item = request.form.get('clothes_img')
    if not selected_item:
        return "옷이 선택되지 않았습니다", 400

    session['selected_item'] = selected_item
    return redirect(url_for('result.loading'))

@result_bp.route('/dress/loading')
def loading():
    if 'user' not in session:
        flash("로그인 후 이용해주세요.")
        return redirect(url_for('login.login_page'))

    photo_path = session.get('photo_path')
    selected_item = session.get('selected_item')
    if not photo_path or not selected_item:
        return redirect(url_for('upload.upload'))

    return render_template('loading.html', stage='업로드된 이미지 정합성 체크', redirect_url=url_for('recommend.recommend'))

@result_bp.route('/dress/<path:item>')
def result(item):
    if 'user' not in session:
        flash("로그인 후 이용해주세요.")
        return redirect(url_for('login.login_page'))

    photo_path = session.get('photo_path')
    if not photo_path:
        return redirect(url_for('upload.upload'))

    return render_template(
        'result.html',
        result=photo_path,
        item=item,
        user=session.get('user'),
        previous=url_for('recommend.recommend')
    )