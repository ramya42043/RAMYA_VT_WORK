from flask import Flask, render_template

app = Flask(__name__)

@app.route("/hello")
def return_hello():
	return render_template("hello.html") 

@app.route("/login")
def return_login():
	return render_template("login.html")

@app.route("/validate", methods=['GET', 'POST'])
def print_uname():
	return "hello there" 


if __name__ == "__main__":
	app.run(debug=True)
