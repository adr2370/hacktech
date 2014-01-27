#StoryTeller
##Built at HackTech Winter 2014
  + Alex Ramirez
  + Brian Kim
  + Shahid Chohan



##Plain and simple:
Turn any picture of text into an audio book. Take a photo of a book page from your phone or choose a screenshot of an e-book and have it read back to you as an .mp3 audio file.

Whether you feel more like listening to words rather than reading them, or if you're on the go and want to keep your hands and eyes free while still taking in information, our app will be able to turn anything you want into more convenient and playable audio.

Smart splicing together of audio files based on punctuation marks allows for natural sounding pauses and voice flow.

##HackTech, The tech behind the hack:
- iOS iPhone application to take or choose existing photo and play or pause the audio
- OpenCV and Tesseract OCR written in C++, optimized to make sure page is upright and contrast between dark and light text is apparent
- Python flask application that receives a POST request containing the image, runs the c++ code, and receives the extracted text
- The text is separated into segments by punctionation and sent through Google's Text to Voice API
- The separate mp3 files are then stitched together to create an mp3 that is then played back on the phone that can be paused and resumed as the user pleases.

##Future plans (groundwork laid, but not implemented because it's still only a hackathon):
- Utilizing Google Translate API to get the text read out to you in other languages.
- Streaming of entire books found from an excerpt of a book. Snap a picture of a page and get access to the whole book. Think Shazam for books.