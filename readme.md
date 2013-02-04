From: http://iwasdeportedandalligotwasthislousydomain.co.uk/index.php?entry=entry120203-075143

#Introduction

This simple program was thrown together to see if tossing thousands of sausages at lines can be used to calculate PI, described here: 
http://www.wikihow.com/Calculate-Pi-by-Throwing-Frozen-Hot-Dogs

Basically you take a sausage of length N, draw a bunch of lines that are distance N apart, and throw some sausages towards the line.
For every throw, increment a throw counter TC, and for every hotdog that comes to rest crossing a line, increment a cross counter CC.
After you're tired of manhandling sausages, calculate PI by doing: pi = TC * (2 / CC)

There are many better ways to do this, this was simply the quickest way I knew to code it up for instant gratification.
For what it's worth, this had PI accurate to 6 digits after a few million iterations (and was no better off after a few trillion)

#Note

It turns out that adjusting the hotdogWidth to be anything but 0.0f tosses the estimate/convergence out quite a bit.
So for now, we're throwing _really_ thin needles instead (instead of a width of 0, I guess you could make a really long and thin needle too).