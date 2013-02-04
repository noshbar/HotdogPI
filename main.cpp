/*
 This simple program was thrown together to see if tossing thousands of sausages at lines can be used to calculate PI, described here: 
 http://www.wikihow.com/Calculate-Pi-by-Throwing-Frozen-Hot-Dogs
 Basically you take a sausage of length N, draw a bunch of lines that are distance N apart, and throw some sausages towards the line.
 For every throw, increment a throw counter TC, and for every hotdog that comes to rest crossing a line, increment a cross counter CC.
 After you're tired of manhandling sausages, calculate PI by doing: pi = TC * (2 / CC)

 There are many better ways to do this, this was simply the quickest way I knew to code it up for instant gratification.
 For what it's worth, this had PI accurate to 6 digits after a few million iterations (and was no better off after a few trillion)

 NOTE: It turns out that adjusting the hotdogWidth to be anything but 0.0f tosses the estimate/convergence out quite a bit.
       so for now, we're throwing _really_ thin needles instead.
	   (instead of a width of 0, I guess you could make a really long and thin needle too)
*/

#define _USE_MATH_DEFINES //to calculate some things, and compare our answer to M_PI, we need to set this define, so that math.h exposes it
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>       //for int64 support

int main(int argc, char *argv[])
{
	uint64_t tosses         = 0;                             //total number of tosses
	uint64_t crosses        = 0;                             //how many hotdogs came to rest crossing a line
	double   hotdogWidth    = 0.0f;                          //the width of the hotdog, defines the radius of the cap at the end
	double   capRadius      = hotdogWidth / 2.0f;            //the radius of the round bits/cap at the end
	double   shaftLength    = 1.0f;                          //the length of the hotdog shaft, that is, only of the straight parts, excluding the curved ends
	double   halfShaft      = shaftLength / 2.0f;            //we're working with circles centered around 0, so it makes sense to have some radius's pre-calculated
	double   totalLength    = shaftLength + (2 * capRadius); //the total length is the length of the shaft, plus both caps on the end
	int      output         = 0;                             //a toggle we use to show output

	double   best           = 0;                             //the best estimate of PI so far, could be a random one off chance, but meh
	double   bestDifference = 1000;                          //the difference between the best PI and real PI, start high so that our first hit should be lower
	uint64_t bestToss       = 0;                             //the iteration the best mostly-PI happened on

	//kick off the random number generator
	srand(time(NULL));

	while (1)
	{
		//pick a random position
		double x = (rand() / (double)RAND_MAX) * totalLength;
		double y = (rand() / (double)RAND_MAX) * totalLength;

		//pick a random angle, where angle = (random percent * PI), seeing as cos and sin use radians.
		double angle = (rand() / (double)RAND_MAX) * M_PI;

		//we center our hotdog around 0 initially, meaning that the tip of one end rotated at our random angle will be at cos(angle) and sin(angle)
		//we only use halfShaft as the length, we will cater for the caps later
		double xOffset = (cos(angle) * halfShaft);
		double yOffset = (sin(angle) * halfShaft);

		//seeing as we only calculated one tip, we need to find the opposite one. as we were rotating around zero, we can simply invert the points in space by multiplying them by -1.
		//also in this step, we move them to our random position
		double x1 = x - xOffset;
		double y1 = y - yOffset;
		double x2 = x + xOffset;
		double y2 = y + yOffset;

		//now we have the positions of the two ends of the _shaft_, from these points, we can simply add the radius of the caps either way and see if they cross a line
		if ( (x1 + capRadius >= totalLength) || (x2 + capRadius >= totalLength) || (x1 - capRadius <= 0) || (x2 - capRadius <= 0) )
			crosses++;

		//now work our sort-of PI out using the magic formula
		double kindaPi    = tosses * (2 / (double)crosses);
		double difference = M_PI - kindaPi;
		//if this is our best PI yet, store it for safe keeping
		if (fabs(difference) < fabs(bestDifference))
		{
			best           = kindaPi;
			bestDifference = difference;
			bestToss       = tosses - 1;
		}

		tosses++;

		output++;
		if (output == 10000000)
		{
			printf("tosses\t\t= %lld\n", tosses);
			printf("crosses\t\t= %lld\n", crosses);
			printf("~pi\t\t= %.15f\n", kindaPi);
			printf("pi\t\t= %.15f\n", M_PI);
			printf("difference\t= %f\n", difference);
			printf("best so far\t= %.15f (difference: %.15f @ %lld)\n", best, fabs(bestDifference), bestToss);
			printf("\n");
			output = 0;
		}
	}

	return 0;
}
