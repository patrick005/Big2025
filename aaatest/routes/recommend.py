# from flask import Blueprint, render_template, session, redirect, url_for, request, flash

# recommend_bp = Blueprint('recommend', __name__)

# @recommend_bp.route('/recommend', methods=['GET', 'POST'])
# def recommend():
#     if 'user' not in session:
#         flash("추천을 받으려면 로그인해주세요.")
#         return redirect(url_for('login.login_page'))

#     if request.method == 'POST':
#         selected_item = request.form.get('clothes_img')
#         if not selected_item:
#             return "옷이 선택되지 않았습니다", 400

#         session['selected_item'] = selected_item
#         return render_template(
#             'loading.html',
#             stage='가상 피팅',
#             redirect_url=url_for('result.result', item=selected_item)
#         )

#     photo_path = session.get('photo_path')
#     if not photo_path:
#         return redirect(url_for('upload.upload'))

#     items = [
#         {"name": "블레이저", "image": "/static/clothes/blazer.png"},
#         {"name": "셔츠", "image": "/static/clothes/shirt.png"},
#         {"name": "가디간", "image": "/static/clothes/cardigan.png"}
#     ]

#     return render_template(
#         'recommend.html',
#         photo=photo_path,
#         items=items,
#         user=session.get('user')
#     )
from flask import Blueprint, render_template, session, redirect, url_for, request, flash

recommend_bp = Blueprint('recommend', __name__)

@recommend_bp.route('/recommend', methods=['GET', 'POST'])
def recommend():
    if 'user' not in session:
        flash("추천을 받으려면 로그인해주세요.")
        return redirect(url_for('login.login_page'))

    if request.method == 'POST':
        selected_item = request.form.get('clothes_img')
        if not selected_item:
            return "옷이 선택되지 않았습니다", 400

        session['selected_item'] = selected_item
        return render_template(
            'loading.html',
            stage='가상 피팅'
        )

    photo_path = session.get('photo_path')
    if not photo_path:
        return redirect(url_for('upload.upload'))

    items = [
        {"name": "블레이저", "image": "/static/clothes/blazer.png"},
        {"name": "셔츠", "image": "/static/clothes/shirt.png"},
        {"name": "가디간", "image": "/static/clothes/cardigan.png"}
    ]

    return render_template(
        'recommend.html',
        photo=photo_path,
        items=items,
        user=session.get('user')
    )