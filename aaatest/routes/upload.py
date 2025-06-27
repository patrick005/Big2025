# from flask import Blueprint, render_template, request, redirect, session, url_for, current_app, flash
# from werkzeug.utils import secure_filename
# import os
# from models import db

# upload_bp = Blueprint('upload', __name__)

# @upload_bp.route('/upload', methods=['GET', 'POST'])
# def upload():
#     if 'user' not in session:
#         flash("업로드하려면 먼저 로그인해주세요.")
#         return redirect(url_for('login.login_page'))

#     if request.method == 'POST':
#         if 'photo' not in request.files:
#             return "No photo part in the request", 400
#         file = request.files['photo']
#         if file.filename == '':
#             return "No selected file", 400

#         filename = secure_filename(file.filename)
#         file_path = os.path.join(current_app.config['UPLOAD_FOLDER'], filename)
#         file.save(file_path)
#         session['photo_path'] = file_path

#         return render_template('loading.html', stage='업로드된 이미지 적합성 체크', redirect_url=url_for('recommend.recommend'))

#     return render_template('upload.html', user=session.get('user'))
# aaatest/routes/upload.py
from flask import Blueprint, render_template, request, redirect, session, url_for, current_app, flash, jsonify
from werkzeug.utils import secure_filename
import os
from models import db
from test_python_only.upload_img_check import check_uploaded_image

upload_bp = Blueprint('upload', __name__)

@upload_bp.route('/upload', methods=['GET', 'POST'])
def upload():
    if 'user' not in session:
        flash("업로드하려면 먼저 로그인해주세요.")
        return redirect(url_for('login.login_page'))

    if request.method == 'POST':
        if 'photo' not in request.files:
            return "No photo part in the request", 400
        file = request.files['photo']
        if file.filename == '':
            return "No selected file", 400

        filename = secure_filename(file.filename)
        file_path = os.path.join(current_app.config['UPLOAD_FOLDER'], filename)
        file.save(file_path)
        session['photo_path'] = file_path

        # loading.html로 이동 (자바스크립트가 /image_check 호출)
        return render_template(
            'loading.html',
            stage='업로드된 이미지 적합성 체크'
        )

    return render_template('upload.html', user=session.get('user'))

@upload_bp.route('/image_check')
def image_check():
    photo_path = session.get('photo_path')
    if not photo_path:
        return jsonify({'status': 'NO_IMAGE'})

    status = check_uploaded_image(photo_path)
    session['check_result'] = status  # recommend에서 사용할 수 있음

    return jsonify({'status': status})