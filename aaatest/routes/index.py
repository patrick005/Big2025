from flask import Blueprint, render_template, session, redirect, url_for, flash

index_bp = Blueprint('index', __name__)

@index_bp.route('/')
def index():
    return render_template('index.html', user=session.get('user'))

@index_bp.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('index.index'))