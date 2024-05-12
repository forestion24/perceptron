# perceptron
Simple perceptron made from scratch in c++ with a gui input method

# compiling
To compile the program use:

```g++ -o main.cpp-out main.cpp drawing.cpp -lsfml-graphics -lsfml-window -lsfml-system```

# to run it use:
```./main.cpp-out```

I dont care if you use windows.

# debugging and flexing
If you want to see the weights run:

```cat weights.txt | tr -s ' ' '\n' | fold -w 5 | awk '{printf "%6s", $1} NR%800==0 {print ""}' > aligned_weights.txt```

and open aligned_weights.txt.

If the program got any input it will also create `pixels_nice.txt` which is just a slightly formatted version of what it's getting as input.

# usage
After running the program a window of size 800x600 should appear. This is the input. Draw either a non filled circle or rectangle (as that's what it has been "trained" on).

### left click
draw under cursor

### right click
erase under cursor

### backspace
erase entire window

### enter
update the input without actually inputting it (mostly for debugging)

### space
input - after this switch to terminal to see the output