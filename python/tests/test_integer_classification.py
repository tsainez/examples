import subprocess
import sys
import unittest

class TestIntegerClassification(unittest.TestCase):
    def test_largest_odd_integer(self):
        # Inputs:
        # Problem 1: Name "TestUser"
        # Problem 2: Integer "2" (Even)
        # Problem 3: 10 integers (1-10)
        # Problem 4: 10 negative odd integers (-1, -3, ... -19)

        inputs = []
        inputs.append("TestUser") # P1
        inputs.append("2")        # P2

        # P3 inputs
        for i in range(1, 11):
            inputs.append(str(i))

        # P4 inputs: -1, -3, -5, -7, -9, -11, -13, -15, -17, -19
        # Largest is -1.
        for i in range(10):
            inputs.append(str(-(2*i + 1)))

        input_str = "\n".join(inputs) + "\n"

        process = subprocess.Popen(
            [sys.executable, "python/integer-classification.py"],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

        stdout, stderr = process.communicate(input=input_str)

        # Print output for debugging
        if stderr:
            print("STDERR:", stderr)

        expected_output_fragment = "The largest odd integer in the stack is -1."
        self.assertIn(expected_output_fragment, stdout, "Code failed to find largest odd integer among negatives.")

if __name__ == "__main__":
    unittest.main()
