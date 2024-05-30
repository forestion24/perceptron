# perceptron
Simple perceptron (affectionally named Alfred) made from scratch in c++ with a gui input method

before everything else, make alignWeights.sh and resetWeights.sh executable.

```bash
chmod 744 alignWeights.sh resetWeights.sh
```

# compiling
To compile the program use:

```bash 
g++ -o main.cpp-out main.cpp drawing.cpp Perceptron.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

# to run it use:
```bash
./main.cpp-out
```

I dont care if you use windows.

# debugging and flexing
If you want to see the weights open aligned_weights.txt, the weights are aligned as the program is used.

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

# accuracy
The accuracy is ~59.2% on account of my bad drawing skills and small data set