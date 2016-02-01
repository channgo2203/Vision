#SideWalkDetection Algorithm

##Abstract
In this paper, we present a method which can detect sidewalks based on line detection. The main function of it is that induce pedestrians to follow right ways to across sidewalks. Most sidewalk detection algorithms use color histogram analysis to extract the area of sidewalk. However, our algorithm is based on the line detection because there are various kinds of patterns and colors used in detecting sidewalks all over the world. We applied some image filters that get derivatives of images and calculating line with some regression methods. It is performed using a Walking Assistance Mobile Application for visually impaired people and can be used in no extra device and technology.


##Introduction
As the technology has been renovated each day, more convenient life for ours are also required. In our society, there are some obstacles that visually impaired person have to go through in living high dense urban. Walking in road, as a pedestrian, it's so hard for them to go straight with no visual guide that help recognizing sidewalk's circumstance. To solve this problem, there are some sidewalk detection method, one by Seng(Seng, John S., and Thomas J. Norrie. "Sidewalk following using color histograms." Journal of Computing Sciences in Colleges 23.6 (2008): 172-180.) and so on. But they extracted data based on color models of histogram and analyzed that to get information. Thus, in practice, color models won't work properly and such as existing some noise at image, it's reliability will be suspected of. So, we determined to develop algorithms based on line detection method and set two main focus of it. 

First is that the algorithm is need to be based on line detection. To cope every situation that occur in real world's sidewalk such as fallen leaves, disarranged blocks and so on, we constructed the sidewalk detecting algorithm's as linear based. We get the line features of the image that has more reliability to be a sidewalk and analysis the most data to get more accuracy and less elapsed time. We reduced it's time complexity by combining brief algorithm's result which operated in each video frame and analysis by some statistical regression method. It's result are more accurate than just adopting single complicated function to each input video frame and more faster than just doing complicated algorithm to each video frames. So we made some brief formula that testify the line's reliability and features to find whether the lines' are worth to regard as sidewalk or not. 


Second is that the algorithm should work in real-time, as designed for visually impaired person and used in walking. In order to cope with each situation, it required that it's elapsed time be less than user's walking time and it be no spurious response and have high accuracy rating in finding sidewalk result and result's trend. In case of some spurious response happened, users only to believe program and follow the way what said to be result of algorithms. So if the conclusion is not suited for actual sidewalk, it is going to be a big problem and the algorithms' performance will be discussed. Also, if sidewalk's tendency is trembled as every steps of user, it is hard to user to recognize what is actual following path, as there exist so many path as they walk. In short, it is necessary to reduce elapsed time as work in real-time and to improve algorithms accuracy not to confuse user by final result. 


So in order to achieve this two purpose, with the help of computer vision, we have developed a Walking Assistance Android Application(WAAA) for the visually impaired. In order to develop WAAA, therefore, we need algorithms that can detect sidewalks and extract the surrounding noise. At first, we planed to use color histogram analysis to detect sidewalk. We studied various algorithms concerning sidewalk detection, and we found a algorithm which based on color histogram analysis. And it works reliably on the ideal sidewalk situation, which there are only one pattern and color, also no unexpected noise. But it turned out that, in reality, it don’t work well. Because sidewalk can be covered partly with the shadow of trees, some kind of obstacles, other pedestrians or abnormal pattern and color. For this reason, we need to make another algorithms that don’t use color histogram as much as we can. Finally, we decided to make an algorithm based on line detection. Through this solution, we could solve limitations which are caused by color histogram.


In this paper, we focus on the line detection and tendency of real-time images. We have studied how visually impaired people are walking on the sidewalk and what can usually happen in real world. It means that there are many fallen leaves. There are some pedestrians and many colors of blocks. Besides, there might be some corners where people must turn the direction at sidewalks. So, we made algorithms to solve these problems by line detection.


In our method, we increase the reliability of direction by comparing the subsequent video frames with that of real-time's. It has little to do with machine learning, but it looks for accumulated input data set and evaluates the actual direction of pedestrian wants just like machine learning does. The goal of this algorithm is to detect the direction of users and he or she should follow. It gives users the information on which ways are better to follow and how to do that. As this algorithm is applied to WAAA, visually impaired people can recognize the correct direction and can make a decision about his or her way.

##Related Works

There are some algorithm that can detect lines in real-time. Such as sidewalk, automobile's lane. Algorithms for drone and automobile are actively discussed. Such as color based road following algorithms and so on like Color-based road detection in urban traffic scenes

In previous ones, there are mostly depends on colors of images. A benchmark road follower system, SCARF[Supervised Classification Applied to Road Following]also uses Gaussian color model too. However, There are many limitations in applying  algorithms in real world. So, we gave up using the road detection system using Color Histogram and utilized edge detection along with road shape model to detect road areas in an image. Adopting this system, we made a blueprint in our research. Contrary to their studies, we used line detection and linear regression to get reliable line in ours and accumulated the tendency lines and found the direction of user. 

We first had to apply some filter to reduce noise of the image. Tomasi[Bilateral filtering for gray and color images] has presented the Bilateral filter by way of reduce noise of the image. It is smoothing filter for images that is characterized by being non-linear, edge-preserving, and noise-reducing. G Deng [An adaptive Gaussian filter for noise reduction and edge detection]{deng1993adaptive} has present an adaptive Gaussian filter for noise reduction and edge detection. In order to get more specific information of image, although Bilateral filter has more time complexity than Gaussian's, we adopted the previous one. Tomas has present the way to use this filter in RGB or other color model images.

After applying filters, we need to find contours of the image. To detect the image's edge, we choose Canny detection method by J. Canny[A computational approach to edge detection.] Canny detection has got a two threshold to find contours. By adjusting two weighting value, it find edges by Sobel edge detector. After that, it check each edge's magnitude is maximum. If it is maximum, it only apply it and connect with other edges. It has got low error ratio, no spurious response, and well localized algorithm. It's result has mainly affected by this parameter. But defining two threshold's value is not easy. So P Bao [Canny edge detection enhancement by scale multiplication.] has suggested scale multiplication to enhance the quality of detection. In our algorithm, we resized the image frame and set value by some test.

To adjust appropriate threshold, video frame's color is need to be equalized. Histogram Equalization(HE) method is well known algorithm to revise image. Shah [A REVIEW ON IMAGE CONTRAST ENHANCEMENT TECHNIQUES USING HISTOGRAM EQUALIZATION] arranged this method to use. We equalized the video frame before applying The filter. The image is well-ordered by resizing and equalizing method. There are some adaptive filters. But our work is real-time image processing and needed to be operated in less time complexity. So we just set the threshold as a constant value by evaluating before the program run. 


In order to detect sidewalks, we have to find some lines in the image. There are many algorithms that find images's line. But our algorithm is primarily based on the Probabilistic Hough Transform. Probabilistic Hough Transform(PHT) by Kiryati[A probabilistic Hough transform] and Progressive Hough Transform(PPHT) by Barinova [On detection of multiple object instances using hough transforms] are good way to detect line features in the image. It is a technique which can be used to isolate features of a particular shape within a image. By adopting this function to contours, we get line features of each image frame. 
Succeeding finding lines of image, we verified each line's reliability by some equations. 

Finally, we get two most reliable lines on each video frame and accumulated it. Subsequently, we do linear regression on stacked lines. Seber[Linear Regression Analysis]has arranged some linear regression method. Such as Ordinary Least Squares(OLS), Generalized Least Squares(GLS), Total Least Squares(TLS) and so on. Despite the fact that GLS and TLS is more reliable for analyzing data, we chose OLS to get relatively less elapsed time to be real-time processing. It is popular and powerful estimator whose result line has to go through average of the points. We, so as to, adopted OLS estimator to apply regression in get better results.