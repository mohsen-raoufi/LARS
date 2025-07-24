"""
This code hosts all the general functions needed to run the post processing, including the file reading, and analysis.

Author: Mohsen Raoufi
Date: 2025-07-23
Version: 1.0
"""
import os
import sys
import pandas as pd
import numpy as np
import pickle as pkl
from tqdm import tqdm

import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter

import seaborn as sns

import re

import warnings
# warnings.filterwarnings("ignore")


def find_all_txt_files(experiment_dir):
    # Find all the .txt files in the experiment directory
    files = [f for f in os.listdir(experiment_dir) if f.endswith('.txt')]
    return files

def find_log_files_from_list_of_files(files):
    # filter the files into LARS_LOG_only (for those that are logged without the video recording)
    LARS_Log_only_files = [f for f in files if 'LARS_LOG_' in f and 'only' in f]

    # and the others that does not have only after the LARS_LOG_

    # LARS_Log = [f for f in files if 'LARS_LOG_2025' in f]
    LARS_Log = [f for f in files if 'LARS_LOG_' in f and 'only' not in f]

    return LARS_Log_only_files, LARS_Log

def print_file_list(files):
    # Print the list of files
    print("Files found:")
    for i, f in enumerate(files):
        print(f"{i + 1:3d}: {f}")

def get_lines_from_file(file_name, experiment_dir):
    """
    Reads lines from a file and returns them as a list.
    """
    txt_file_path = os.path.join(experiment_dir, file_name)
    with open(txt_file_path, 'r') as file:
        lines = file.readlines()
    return lines

def get_df_from_file(file_name, experiment_dir, skip_header=True, nskip_header=9, log_str='log_only', debug=False):
    """
    Reads a file and returns a DataFrame with the parsed data.
    """
    if debug:
        print(f"Reading file: {file_name} from {experiment_dir}")

    # Read the lines from the file
    lines = get_lines_from_file(file_name, experiment_dir)
    
    # Skip header lines if specified
    if skip_header:
        lines = lines[nskip_header:]
    else: 
        warnings.warn("Warning: No header lines skipped. This may lead to incorrect parsing if the file has a header.")
    
    # Parse the lines into a DataFrame
    data = []
    last_timestamp = None
    for line in lines:
        if line.strip():  # Check if the line is not empty
            parsed_line, last_timestamp = parse_log_line_with_positions_list(line, last_timestamp)
            data.append(parsed_line)
    
    df = pd.DataFrame(data)
    
    # Add additional columns
    df['file_name'] = file_name
    df['experiment_dir'] = experiment_dir
    df['log_str'] = log_str

    # match = re.search(r'_N_(\d+)_', file_name)
    # if match:
    #     number_str = match.group(1)
    #     N = int(number_str)
    #     if(debug): print(f"Extracted number: {N}")
    #     df['N'] = N
    # else:
    #     warnings.warn("Warning: Couldn't extract N from file name. Ensure the file name contains '_N_' followed by a number.")

    # # Check if N and the number of positions are the same
    # if not (df['N'] == df['positions'].apply(len)).all():
    #     warnings.warn("Warning: The number of positions does not match the value of N in the file name.")

    return df

def get_all_dfs_from_file_list(files_list, experiment_dir, skip_header=True, nskip_header=9, log_str='log_only', debug=False):
    """
    Reads multiple files and returns a DataFrame with the parsed data from all files.
    """
    all_dfs = []
    for i_file, file_name in enumerate(tqdm(files_list, desc="Processing files")):
        if debug:
            print(f"Reading file {i_file+1}/{len(files_list)}: {file_name}")
        df = get_df_from_file(file_name, experiment_dir, skip_header, nskip_header, log_str, debug)
        all_dfs.append(df)
    if all_dfs:
        unified_df = pd.concat(all_dfs, ignore_index=True)
        return unified_df
    else:
        print(f"No log files found")
        return pd.DataFrame()
    
    
    return unified_df

def parse_log_line_with_positions_list(line, last_timestamp=None):
    """
    Parses a single log line into a dictionary, with robot positions
    stored as a list of dictionaries.
    """
    parts = line.strip().split('\t')
    
    fps = int(parts[0])
    timestamp = int(parts[1])

    if last_timestamp is not None:
        fps_calc = 1000 / (timestamp - last_timestamp) if (timestamp - last_timestamp) > 0 else 0
    else:
        fps_calc = 0
    last_timestamp = timestamp

    positions = []
    control_var = None
    
    # Iterate through robot data starting from index 2
    # Each robot has ID, X, Y - 3 parts
    i = 2
    N = 0
    
    while i < len(parts):
        try:
            robot_id = int(parts[i])
            x_coord = int(parts[i+1])
            y_coord = int(parts[i+2])
            # positions.append({'id': robot_id, 'x': x_coord, 'y': y_coord}) # append a dictionary
            positions.append(np.array([robot_id, x_coord, y_coord])) # append a numpy array
            # Append a Pandas Series for each robot
            # positions.append(pd.Series({'id': robot_id, 'x': x_coord, 'y': y_coord}))
            N = N + 1
            i += 3
        except (ValueError, IndexError):
            # If we hit an error, it means we've either reached the end of robot data
            # or the last element is the control_var.
            # Assuming the last remaining part is the control_var if it's not a full [ID, X, Y] triplet.
            if i == len(parts) - 1: # Check if it's the very last element
                try:
                    control_var = int(parts[i])
                except ValueError:
                    control_var = None # Not a valid int, keep as None
            break # Exit the loop as we can't parse more robot data
            
    return {
        'FPS': fps,
        'FPS_calc': fps_calc,
        'Time': timestamp,
        'positions': positions,
        'control_var': control_var ,
        'N': N
    }, last_timestamp
