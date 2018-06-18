from flask import Flask, render_template, request
import MySQLdb

app = Flask(__name__)

@app.route("/", methods=['GET'])
def login():
	return render_template("login.html")

@app.route("/auth", methods=['POST'])
def authorize():
	if request.form.get('login') == "Login":
		uname = request.form.get('username')
		pwrd = request.form.get('password')
		try:
			conn = MySQLdb.connect(user='root', passwd='admin@123', db='students')
			c = conn.cursor()
			c.execute('select password from student_info where username=%s', (uname, ))
			pw = (c.fetchone())[0].strip()

			if pw == pwrd:
				return render_template("success.html", uname=uname)
			else:
				return render_template("error.html")
		except:
			return render_template("error.html")
		finally:
			conn.close()
	return render_template("signup.html")

@app.route("/create_user", methods=['POST'])
def create_user():
	uname = request.form.get('username')
	pwrd = request.form.get('password')
	try:
		conn = MySQLdb.connect(user='root', passwd='admin@123', db='students')
                c = conn.cursor()
		c.execute('insert into student_info(username, password)values(%s, %s)', (uname, pwrd))
		conn.commit()
		return render_template('create_user_success.html', uname=uname)
	except:
		return render_template('create_user_error.html', uname=uname)
	finally:
		conn.close()

		
if __name__ == "__main__":
	app.run(debug=True)
