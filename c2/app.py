from flask import Flask, request

app = Flask(__name__)

@app.route("/communication", methods=["GET", "POST"])
def index():
	print(request.data)
	return "response"

if __name__ == '__main__':
      app.run(host='0.0.0.0', port=8080)
