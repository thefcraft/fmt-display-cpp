import os
import shutil

# Define the root output directory (where the .html files are generated)
os.chdir(os.path.dirname(__file__))
os.chdir('..')

def mover(out_dir):
    for file in os.listdir(out_dir):
        if file.endswith('.html') and file != 'index.html' and file != '404.html':
            # Generate the target directory and file path
            file_path = os.path.join(out_dir, file)
            dir_name = file.removesuffix('.html')
            target_dir = os.path.join(out_dir, dir_name)
            target_file = os.path.join(target_dir, 'index.html')
    
            # Create the target directory if it doesn't exist
            if not os.path.exists(target_dir):
                os.makedirs(target_dir)
    
            # Define the new file path for the index.html
            target_file = os.path.join(target_dir, 'index.html')
    
            # Move the file
            print(f"Moving {file_path} to {target_file}")
            shutil.move(file_path, target_file)

mover(out_dir = 'out')
mover(out_dir = os.path.join('out', 'docs'))

print("File move completed!")
