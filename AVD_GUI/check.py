from flask import Flask, render_template, request
import subprocess
from subprocess import PIPE
import os


testcases = {}
tc_file_path = ""
base_dir = os.getcwd()

def get_files(ftype=None):
	global testcases
	global tc_file_path
        tc_file_path = os.path.join(base_dir, 'Testcases', ftype)
        tc_files = [i for i in os.listdir(tc_file_path) if i.endswith(".py")]
	
	tc_file_count = len(tc_files)

	for i in range(1, tc_file_count+1):
		testcases['Testcase'+str(i)] = tc_files[i-1]
	return testcases

app = Flask(__name__)

@app.route("/", methods=['GET'])
def return_home():
	return render_template("home.html")

@app.route("/audio", methods=['GET'])
def return_audio():
	testcases = get_files(ftype='audio') 
	return render_template("audio.html", tcases=testcases)



@app.route("/video", methods=['GET'])
def return_video():
        testcases = get_files(ftype='video') 
        return render_template("video.html", tcases=testcases)
@app.route("/camera", methods=['GET'])
def return_camera():
        testcases = get_files(ftype='camera') 
        return render_template("camera.html", tcases=testcases)


@app.route("/testcases", methods=['POST'])
def execute_cases():
	items = request.form.getlist('Testcase')
	print "items:", items
	status = {} 
	for item in items:
		#print "testcase name:", testcases[item]
		item = str(item)
		os.chdir(tc_file_path)
		process = subprocess.Popen('python {0}'.format(testcases[item]), stdout=PIPE, shell=True)  
		status[item] = (process.communicate()[0]).strip()
		os.chdir(base_dir)
	#print "status:", status

	return render_template("status.html", status=status)
		
if __name__ == "__main__":
	app.run(debug=True)
	
