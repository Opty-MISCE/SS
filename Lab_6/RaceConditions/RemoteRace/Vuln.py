from flask import Flask, request, redirect, url_for, make_response, render_template
from flask_sqlalchemy import SQLAlchemy
from functools import wraps
import os
import sys
import hashlib

# Setup App
app = Flask(__name__)
COOKIE_TOKEN = "JTOKEN"

# Setup DB
db_path = "/tmp/flask_server.db"
app.config["SQLALCHEMY_DATABASE_URI"] = 'sqlite:///%s' % (db_path)
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False
db = SQLAlchemy(app)

# Read Flag
try:
    with open('/home/ctf/flag', 'r') as f:
        FLAG = f.read()
except Exception as e:
    FLAG = "SSof{Failed_to_get_the_flag. Contact an admin to fix it! Sry!}"


def error(msg):
    return render_template('error_response.html', msg=msg)


# ================
# === SESSIONS ===
# ================
class Session(db.Model):
    """
    Associates a session token with its respective user
    """
    id = db.Column(db.Integer, primary_key=True)
    # @FIXME: Should be a Foreign Key, Oh Well XD
    jtoken = db.Column(db.Text(), unique=True)
    username = db.Column(db.Text())

    def __init__(self, username=None):
        self.jtoken = os.urandom(64).encode('hex')
        self.username = username

    def __repr__(self):
        return '<Session %s>' % (self.jtoken)


def get_current_session(jtoken=None):
    if not jtoken:
        jtoken = request.cookies.get(COOKIE_TOKEN)
        if not jtoken:
            print
            "[WARNING] This should never happen"
            return None

    return Session.query.filter_by(jtoken=jtoken).first()


@app.context_processor
def templates_utility():
    return dict(get_current_session=get_current_session)


# Runs Before Every Request
@app.before_request
def setup_session():
    def add_session_and_redirect():
        new_session = Session()
        db.session.add(new_session)
        db.session.commit()

        response = make_response(redirect(request.path))
        response.set_cookie(COOKIE_TOKEN, new_session.jtoken)
        return response

    if COOKIE_TOKEN not in request.cookies:
        return add_session_and_redirect()

    current_session = get_current_session()
    if current_session is None:
        return add_session_and_redirect()


def login_required(func):
    @wraps(func)
    def decorated_function(*args, **kwargs):
        current_session = get_current_session()
        if not current_session or current_session.username is None:
            return redirect(url_for('login'))
        else:
            return func(*args, **kwargs)

    return decorated_function


# ================
# ==== Users =====
# ================
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.Text(), unique=True)
    password = db.Column(db.Text())

    def __init__(self, username, password):
        self.username = username
        self.password = self.hash_pwd(password)

    def __repr__(self):
        return '<User %s>' % (self.username)

    @staticmethod
    def hash_pwd(pwd):
        return hashlib.sha512(pwd).hexdigest()


# ================
# ==== VIEWS =====
# ================
@app.route('/')
def home():
    return render_template('home.html')


@app.route('/jackpot', methods=['GET'])
@login_required
def jackpot():
    current_session = get_current_session()

    if current_session.username == 'admin':
        msg = FLAG
    else:
        msg = "No luck... Maybe next time!"

    return render_template('jackpot.html', msg=msg)


@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'GET':
        return render_template('register.html')

    username = request.form['username']
    password = request.form['password']
    if not username or not password:
        return error("You need to provide the 'username' and 'password' to register.")

    user = User.query.filter_by(username=username).first()
    if user or 'admin' in username:
        return error("User '%s' already exists." % user.username)

    user = User(username, password)
    db.session.add(user)
    db.session.commit()

    return redirect(url_for('login'))


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        return render_template('login.html')

    username = request.form['username']
    password = request.form['password']
    if not username or not password:
        return error("You need to provide a 'username' and 'password' to login.")

    # Setup Session with Current User
    current_session = get_current_session()
    current_session.username = username
    db.session.commit()

    registered_user = User.query.filter_by(
        username=username, password=User.hash_pwd(password)).first()

    if not registered_user:
        # Login Failed
        current_session.username = None
        db.session.commit()
        return redirect(url_for('login'))

    # @FIXME: Open Redirect
    return redirect(request.args.get('next') or url_for('home'))


@app.route('/logout')
def logout():
    current_session = get_current_session()

    # Remove User from Session
    current_session.username = None
    db.session.commit()

    return redirect(url_for('login'))


def main(host):
    if not os.path.isfile(db_path):
        db.create_all()

    app.config["DEBUG"] = (host == "127.0.0.1")
    app.run(threaded=True, host=host, port=6660)


if __name__ == '__main__':
    if len(sys.argv) >= 2:
        host = sys.argv[1]
    else:
        host = "127.0.0.1"

    main(host)
