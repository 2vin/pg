# pg
Demo code of P&amp;G Hackathon

This repo contains code of the demo presented in P&G Hackathon 2018.

# Dependencies    
Opencv 3.1    
Caffe    

# Compile    
Run ./compile.sh from the directory.   
(Note: Before compiling the program, make sure you download model files and substitute `classification.cpp` from repo in `caffe/examples/cpp_classification/` and edit the corresponding paths in `src/main.cpp` )    

# Usage    
From the root directory, run the following command:   
`./bin/main`

# Guidelines     
This will open a screen with "Search". Click on "Search" icon and it will mode to detect mode. Show the photo in required area and click on the "Green Tick" icon.  This image will be sent to caffe recognizer and result will be displayed on the screen.    
Due to data limitations, the categories are limited to "Cocacola","Vicks","Oral B" & "Duracell" only with around 400 images per category. Once, more data with better quality is added and trained, the results can be improved and scaled easily.

# Training results    
![Alt Text]
