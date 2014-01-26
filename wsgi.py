import os
from shahidsnasty import text_to_speech
from flask import Flask, make_response
from flask import request
app = Flask(__name__)

@app.route("/", methods = ['POST'])
def savePhoto():
    photoData = request.form['image']
    dir = "photos/shahid.jpg"
    fh = open(dir, "wb")
    fh.write(photoData.decode('base64'))
    fh.close()
    command = "./TessOp " + dir
    text = os.popen(command).read()
    mp3 = text_to_speech(text)
    return mp3

if __name__ == "__main__":
    app.debug = True
    app.run()
    
