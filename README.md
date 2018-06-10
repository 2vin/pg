# P&G Hackathon
Demo code of P&amp;G Hackathon

This repo contains code of the demo presented in P&G Hackathon 2018. [Video](https://youtu.be/Y54jZpEWhlk)

# Dependencies    
Opencv 3.1    
Caffe 
Nvidia DIGITS

# Compile   
Step 1. Clone and install `caffe` from this [repository](https://github.com/BVLC/caffe)     
Step 2. Once caffe is installed, go to `caffe/examples/cpp_classification/` directory and substitute the `classification.cpp` file from the one provided in this repository.   
Step 3. Clone this repository using the command:    
        `git clone https://github.com/2vin/pg.git`       
Step 3. Download the [model files](https://www.dropbox.com/s/iowwvz3cy9jlyac) and extract them in suitable directory.    
Step 4. Once everything is done, open the `src/main.cpp` and edit the corresponding paths in following line:    
        `string str = "../caffe/build/examples/cpp_classification/classification.bin '/home/mouz/Desktop/models/deploy.prototxt' '/home/mouz/Desktop/models/snapshot_iter_100.caffemodel' '/home/mouz/Desktop/models/mean.binaryproto' '/home/mouz/Desktop/models/labels.txt' '/home/mouz/Desktop/PG/code-MV/data/query/query.jpg'";`     
Step 5. Run `./compile.sh` from the root directory of the repository to compile the project.   

# Usage    
From the root directory, run the following command:   
`./bin/main`

# Guidelines     
This will open a screen with "Search". Click on "Search" icon and it will mode to detect mode. Show the photo in required area and click on the "Green Tick" icon.  This image will be sent to caffe recognizer and result will be displayed on the screen.    
Due to data limitations, the categories are limited to "Cocacola","Vicks","Oral B" & "Duracell" only with around 400 images per category. Once, more data with better quality is added and trained, the results can be improved and scaled easily.     

# Training results    
![Alt Text](https://raw.githubusercontent.com/2vin/pg/master/p_n_g-digits-88percentAcc.png)     

The current accuracy is around 88%, which can be increased with proper dataset. The dataset used for this demonstration can be found [here](https://www.dropbox.com/s/88vqv3p4au17iz3/Mouz_Data_full.zip?dl=0)    

(Note: This repository contains only the image search part of the whole system. For updates on voice interfacing, check this [repository](https://github.com/2vin/pg_voice))   
