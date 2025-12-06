# Code Examples Repository

This repository serves as a collection of code examples, assignments, algorithms, and small personal projects spanning multiple programming languages. It is designed to demonstrate various coding concepts, data structures, and problem-solving techniques.

## Structure

The repository is organized by programming language, with each language having its own dedicated directory:

*   **`assembly/`**: MIPS assembly code examples, including recursion and basic procedures.
*   **`c/`**: C programs covering basic algorithms, pointers, memory management, and data structures.
*   **`c++/`**: A comprehensive collection of C++ examples, including sorting algorithms, data structures (linked lists, trees, graphs), and object-oriented programming concepts.
*   **`java/`**: Java implementations of AI search algorithms (A*, Greedy, Uniform Cost) and other object-oriented designs.
*   **`matlab/`**: MATLAB scripts for image processing (Hough transform, edge detection), mathematical simulations, and plotting.
*   **`perl/`**: Perl scripts demonstrating string manipulation and validation.
*   **`php/`**: PHP examples ranging from basic scripts to object-oriented database interactions and web forms.
*   **`python/`**: Python scripts for data analysis (Pandas, NumPy), machine learning (scikit-learn), logical puzzles, and Project Euler solutions.
*   **`sql/`**: SQL queries and schema definitions, primarily focused on TPC-H style database operations.
*   **`swift/`**: Swift functions demonstrating functional programming concepts.

## Setup and Usage

Each directory contains source code that can be run with the standard tools for that language.

### Python
Ensure you have Python 3 installed. Some scripts require external libraries like `numpy`, `pandas`, `scikit-learn`, and `matplotlib`.
```bash
pip install numpy pandas scikit-learn matplotlib
python python/<script_name>.py
```

### C / C++
You will need a C/C++ compiler like `gcc` or `g++`.
```bash
# For C
gcc c/<file>.c -o output_name
./output_name

# For C++
g++ c++/<file>.cpp -o output_name
./output_name
```

### Java
Ensure you have the JDK installed. Compile and run the Java files.
```bash
javac java/*.java
java -cp java <ClassName>
```

### PHP
You can run PHP scripts from the command line or serve them using a web server.
```bash
php php/<file>.php
```

### MATLAB
Open the `.m` or `.slx` files in MATLAB to run the scripts or simulations.

### Assembly (MIPS)
You will need a MIPS simulator like MARS or SPIM to run the `.asm` files.

## Documentation

All source files in this repository have been documented with inline comments and docstrings explaining their purpose, parameters, and return values.

## License

See the [LICENSE](LICENSE) file for details.
