import subprocess
import os

FILE_NAME = "PHATQUA.cpp"  # Change this to your .cpp file name

def main():
    exe_file = os.path.splitext(FILE_NAME)[0]

    # Compile the .cpp file
    compile_cmd = ["g++", FILE_NAME, "-o", exe_file]
    compile_proc = subprocess.run(compile_cmd, capture_output=True, text=True)
    if compile_proc.returncode != 0:
        print("Compilation failed:")
        print(compile_proc.stderr)
        return

    # Run the executable
    run_cmd = ["./" + exe_file] if os.name != 'nt' else [exe_file]
    run_proc = subprocess.run(run_cmd, capture_output=True, text=True)
    print("** RUN FINISHED! **")
    # print(run_proc.stdout)
    if run_proc.stderr:
        print("Program errors:")
        print(run_proc.stderr)

if __name__ == "__main__":
    main()