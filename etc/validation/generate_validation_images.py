import os
import numpy as np
import matplotlib.pyplot as plt
import cv2

import argparse

from datetime import datetime

import tqdm

import matplotlib
matplotlib.use("Agg")  # ensures deterministic size handling (especially on Mac)

bg_color = 'gray'  # default background color for the images
bg_color = (0.7, 0.7, 0.7)  # gray color in RGB format
    
# generate a simple picture with a regular grid of circles/disks with specific distance
def generate_grid_image(grid_size = (3,3), circle_radius = 1, point_distance = 2, image_size = (100, 100), output_path= "grid_image.png", circle_perfection = 1.0):
    """
    Generates an image with a grid of circles.
    grid_size: tuple of (width, height) showing the number of circles in the grid
    point_distance: distance between circles in pixels
    output_path: path to save the generated image
    """

    fig, ax = plt.subplots(figsize=(image_size[0]/100, image_size[1]/100), dpi=100)
    fig.patch.set_facecolor(bg_color)
    ax.set_xlim(0, image_size[0])
    ax.set_ylim(0, image_size[1])
    ax.set_aspect('equal')

    # Calculate total grid width and height
    grid_width = (grid_size[0] - 1) * point_distance
    grid_height = (grid_size[1] - 1) * point_distance

    # Calculate the offset to center the grid in the image
    x_offset = (image_size[0] - grid_width) / 2
    y_offset = (image_size[1] - grid_height) / 2

    for i in range(grid_size[0]):
        for j in range(grid_size[1]):
            x = x_offset + i * point_distance
            y = y_offset + j * point_distance
            # make a circle that has jiggle
            
            circle = plt.Circle((x, y), circle_radius, color='blue', fill=True)
            ax.add_artist(circle)

    plt.axis('off')
    # plt.show()
    plt.savefig(output_path, bbox_inches='tight', pad_inches=0)
    plt.close(fig)


# generate a simple picture with a regular grid of robot snapshots from an png file with specific distance
def generate_robot_grid_image(robot_image_path, grid_size=(3, 3), robot_width=50, point_distance=100, image_size=(1000, 1000), output_path="robot_grid_image.png"):
    """
    Generates an image with a grid of robot snapshots.
    robot_image_path: path to the robot image file
    grid_size: tuple of (width, height) showing the number of robot images in the grid
    point_distance: distance between robot images in pixels
    output_path: path to save the generated image
    """
    if not os.path.exists(robot_image_path):
        raise FileNotFoundError(f"Robot image file not found: {robot_image_path}")
    else:
        robot_image = plt.imread(robot_image_path)

    # resize the robot image 
    if robot_image.shape[0] > robot_width or robot_image.shape[1] > robot_width:
        scale_factor = robot_width / max(robot_image.shape[:2])
        robot_image = cv2.resize(robot_image, None, fx=scale_factor, fy=scale_factor, interpolation=cv2.INTER_AREA)

    fig, ax = plt.subplots(figsize=(image_size[0]/100, image_size[1]/100), dpi=100)
    fig.patch.set_facecolor(bg_color)
    ax.set_xlim(0, image_size[0])
    ax.set_ylim(0, image_size[1])
    ax.set_aspect('equal')

    # Calculate total grid width and height
    grid_width = (grid_size[0] - 1) * point_distance
    grid_height = (grid_size[1] - 1) * point_distance

    # Calculate the offset to center the grid in the image
    x_offset = (image_size[0] - grid_width) / 2
    y_offset = (image_size[1] - grid_height) / 2

    # change the background color to gray
    # ax.set_facecolor('lightgray')

    for i in range(grid_size[0]):
        for j in range(grid_size[1]):
            x = x_offset + i * point_distance - robot_image.shape[1] / 2
            y = y_offset + j * point_distance - robot_image.shape[0] / 2
            ax.imshow(robot_image, extent=(x, x + robot_image.shape[1], y, y + robot_image.shape[0]))

    plt.axis('off')
    # plt.show()
    plt.savefig(output_path, bbox_inches='tight', pad_inches=0)
    plt.close(fig)

# generate a sample picture with random non-overlapping robots from the png file of a robot
def generate_robot_image_with_random_robots(robot_image_path, num_robots=10, robot_width=30, image_size=(1000, 1000), output_path="robot_image_with_random_robots.png"):
    """Generates an image with random non-overlapping robots and a robot image.
    robot_image_path: path to the robot image file
    num_robots: number of random robots to generate
    robot_width: width of the robots in pixels
    image_size: size of the output image
    output_path: path to save the generated image
    """

    if not os.path.exists(robot_image_path):
        raise FileNotFoundError(f"Robot image file not found: {robot_image_path}")
    else:
        robot_image = plt.imread(robot_image_path)

    # resize the robot image 
    if robot_image.shape[0] > robot_width or robot_image.shape[1] > robot_width:
        scale_factor = robot_width / max(robot_image.shape[:2])
        robot_image = cv2.resize(robot_image, None, fx=scale_factor, fy=scale_factor, interpolation=cv2.INTER_AREA)

    fig, ax = plt.subplots(figsize=(image_size[0]/100, image_size[1]/100), dpi=100)
    fig.patch.set_facecolor(bg_color)
    ax.set_xlim(0, image_size[0])
    ax.set_ylim(0, image_size[1])
    ax.set_aspect('equal')

    # change the background color to white
    ax.set_facecolor('white')

    
    # Generate random non-overlapping robots points
    robots = []
    for _ in range(num_robots):
        while True:
            x = np.random.randint(robot_width, image_size[0] - robot_width)
            y = np.random.randint(robot_width, image_size[1] - robot_width)
            if all(np.sqrt((x - cx)**2 + (y - cy)**2) >= robot_width * 2 for cx, cy in robots):
                robots.append((x, y))
                break

    # draw the robots at the generated points
    for x, y in robots:
        x -= robot_image.shape[1] / 2
        y -= robot_image.shape[0] / 2
        ax.imshow(robot_image, extent=(x, x + robot_image.shape[1], y, y + robot_image.shape[0]))

    plt.axis('off')
    # plt.show()
    plt.savefig(output_path, bbox_inches='tight', pad_inches=0)
    plt.close(fig)

# generate an animation of a robot moving in the space following a trajectory and bouncing off walls
def generate_robot_animation_simple_trajectory(robot_image_path, trajectory, robot_width=30, image_size=(1000, 1000), robot_speed=1, output_path="robot_animation.mp4", log_output_path=None):
    """
    Generates an animation of a robot moving along a trajectory.
    robot_image_path: path to the robot image file
    trajectory: list of (x, y) tuples representing the robot's trajectory
    image_size: size of the output image
    output_path: path to save the generated animation
    """
    if not os.path.exists(robot_image_path):
        raise FileNotFoundError(f"Robot image file not found: {robot_image_path}")
    else:
        robot_image = plt.imread(robot_image_path)

    # resize the robot image 
    if robot_image.shape[0] > robot_width or robot_image.shape[1] > robot_width:
        scale_factor = robot_width / max(robot_image.shape[:2])
        robot_image = cv2.resize(robot_image, None, fx=scale_factor, fy=scale_factor, interpolation=cv2.INTER_AREA)
    
    robot_image = robot_image.astype(np.float32)
    np.clip(robot_image, 0.0, 1.0, out=robot_image)

    # if the log_output_path is provided, create a log file
    if log_output_path:
        log_file = open(log_output_path, 'w')
        log_file.write("Frame, X, Y\n")
    
    fig, ax = plt.subplots(figsize=(image_size[0]/100, image_size[1]/100), dpi=100)
    fig.patch.set_facecolor(bg_color)
    ax.set_xlim(0, image_size[0])
    ax.set_ylim(0, image_size[1])
    ax.set_aspect('equal')

    # Create a writer object for saving the animation
    writer = cv2.VideoWriter(output_path, cv2.VideoWriter_fourcc(*'mp4v'), 30, (image_size[0], image_size[1]))

    print("Before Loop frame size:", fig.canvas.get_width_height())

    # move the robot from point to point in the trajectory with a specific speed
    for i_node in range(len(trajectory) - 1):
        start = trajectory[i_node]
        end = trajectory[i_node + 1]
        dx = end[0] - start[0]
        dy = end[1] - start[1]
        distance = np.sqrt(dx**2 + dy**2)
        steps = int(distance / robot_speed)

        for step in range(steps + 1):
            x = start[0] + (dx * step / steps) - int(robot_image.shape[1] / 2)
            y = start[1] + (dy * step / steps) - int(robot_image.shape[0] / 2)

            # x = start[0] + int(dx * step / steps) # - int(robot_image.shape[1] / 2)
            # y = start[1] + int(dy * step / steps) #- int(robot_image.shape[0] / 2)

            # get sure that x and y are ints
            # x = int(x)
            # y = int(y)

            # Clear the axis
            ax.clear()
            ax.set_xlim(0, image_size[0])
            ax.set_ylim(0, image_size[1])
            plt.axis('off')
            ax.set_aspect('equal')
            # ax.set_facecolor('lightgray')

            # plot the trajectory line
            # ax.plot(*zip(*trajectory[:i_node + 1]), color='gray', linestyle='--', linewidth=1)

            # Draw the robot at the current position
            ax.imshow(robot_image, extent=(x, x + robot_image.shape[1], y, y + robot_image.shape[0]))

            # # Write the frame to the video file
            fig.canvas.draw()  # force update of the canvas

            w, h = fig.canvas.get_width_height()
            buf = fig.canvas.buffer_rgba()
            frame = np.frombuffer(buf, dtype=np.uint8).reshape((h, w, 4))[:, :, :3].copy()

            # repeat the writing of the frame to the video file for N_rep_frame     
            N_rep_frame = 2
            for _ in range(N_rep_frame):
                writer.write(cv2.cvtColor(frame, cv2.COLOR_RGB2BGR))

            # Log the robot's position
            if log_output_path:
                frame_number = i_node * (steps + 1) + step + 1
                log_file.write(f"{frame_number}, {x + robot_image.shape[1] / 2}, {y + robot_image.shape[0] / 2}\n")

    writer.release()
    plt.close(fig)


# generate animation of multiple robots moving randomly in the space and bounding off walls and each other
def generate_robot_animation_random_robots(robot_image_path, num_robots=10, robot_width=30, image_size=(1000, 1000), robot_speed=1, animation_duration=500, output_path="robot_animation_random_robots.mp4", log_output_path=None):
    """
    Generates an animation of multiple robots moving randomly in the space.
    robot_image_path: path to the robot image file
    num_robots: number of robots to generate
    robot_width: width of the robots in pixels
    image_size: size of the output image
    output_path: path to save the generated animation
    """

    if not os.path.exists(robot_image_path):
        raise FileNotFoundError(f"Robot image file not found: {robot_image_path}")
    else:
        robot_image = plt.imread(robot_image_path)

    # resize the robot image 
    if robot_image.shape[0] > robot_width or robot_image.shape[1] > robot_width:
        scale_factor = robot_width / max(robot_image.shape[:2])
        robot_image = cv2.resize(robot_image, None, fx=scale_factor, fy=scale_factor, interpolation=cv2.INTER_AREA)

    robot_image = robot_image.astype(np.float32)
    np.clip(robot_image, 0.0, 1.0, out=robot_image)

    # if the log_output_path is provided, create a log file
    if log_output_path:
        log_file = open(log_output_path, 'w')
        log_file.write("Frame, Robot ID, X, Y\n")

    fig, ax = plt.subplots(figsize=(image_size[0]/100, image_size[1]/100), dpi=100)
    fig.patch.set_facecolor(bg_color)
    ax.set_xlim(0, image_size[0])
    ax.set_ylim(0, image_size[1])
    ax.set_aspect('equal')
    plt.axis('off')

    # Create a writer object for saving the animation
    writer = cv2.VideoWriter(output_path, cv2.VideoWriter_fourcc(*'mp4v'), 30, (image_size[0], image_size[1]))

    # Initialize random positions and velocities for robots
    robots = [(np.random.randint(robot_width, image_size[0] - robot_width),
               np.random.randint(robot_width, image_size[1] - robot_width),
               np.random.uniform(0, 2*np.pi)) for _ in range(num_robots)]
    
    # make sure that the initial positions of the robots are not overlapping
    for i in range(num_robots):
        while True:
            x, y, theta = robots[i]
            if all(np.sqrt((x - other_x)**2 + (y - other_y)**2) >= robot_width * 2 for j, (other_x, other_y, _) in enumerate(robots) if j != i):
                break
            else:
                x = np.random.randint(robot_width, image_size[0] - robot_width)
                y = np.random.randint(robot_width, image_size[1] - robot_width)
                theta = np.random.uniform(0, 2*np.pi)
                robots[i] = (x, y, theta)
    
    scale_rand_theta = 1/10

    # change the background color to gray
    # ax.set_facecolor('lightgray')

    for _ in tqdm.tqdm(range(animation_duration), desc="Animating robots time"):  # Number of frames in the animation
        ax.clear()
        ax.set_xlim(0, image_size[0])
        ax.set_ylim(0, image_size[1])
        plt.axis('off')
        ax.set_aspect('equal')
        # ax.set_facecolor('lightgray')

        for i in range(num_robots):
            x, y, theta = robots[i]

            theta += np.random.uniform(-np.pi, np.pi) * scale_rand_theta  # Randomly change direction
            
            # Bounce off walls
            # if hitting the vertical (top/bottom) walls
            if x < robot_width or x > image_size[0] - robot_width:
                theta = np.pi - theta
                x = max(robot_width, min(x, image_size[0] - robot_width))
            # if hitting the horizontal (left/right) walls
            if y < robot_width or y > image_size[1] - robot_width:
                theta = -theta
                y = max(robot_width, min(y, image_size[1] - robot_width))

            theta = theta % (2 * np.pi)  # Normalize angle to [0, 2π]

            vx = robot_speed * np.cos(theta)
            vy = robot_speed * np.sin(theta)

            # Bounce off other robots
            for j in range(num_robots):
                if i != j:
                    x2, y2, theta2 = robots[j]

                    dx = x2 - x
                    dy = y2 - y
                    distance = np.hypot(dx, dy)

                    if distance < robot_width:  # collision
                        # Normalize direction vector
                        nx = dx / distance
                        ny = dy / distance

                        # Reflect velocity vector across the normal
                        dot = vx * nx + vy * ny
                        vx_reflected = vx - 2 * dot * nx
                        vy_reflected = vy - 2 * dot * ny

                        # Update heading based on reflected velocity
                        theta = np.arctan2(vy_reflected, vx_reflected) + np.random.uniform(-np.pi, np.pi) * 3 * scale_rand_theta  # Randomly change direction

                        # Optional: push robots apart to avoid overlap
                        overlap = 0.05 * (2 * robot_width - distance + 1e-6)
                        x -= nx * overlap
                        y -= ny * overlap


            # Update position
            x += vx
            y += vy

            # Update the robot's position and velocity
            robots[i] = (x, y, theta)
            # x -= robot_image.shape[1] / 2
            # y -= robot_image.shape[0] / 2
            

            # Draw the robot at the current position
            ax.imshow(robot_image, extent=(x-robot_image.shape[1] / 2, x + robot_image.shape[1] / 2, y-robot_image.shape[0] / 2, y + robot_image.shape[0] / 2))


            # Log the robot's position
            if log_output_path:
                frame_number = _ + 1
                if i == 0:  # Log only the first robot in each frame
                    log_file.write(f"{frame_number}, {i}, {x + robot_image.shape[1] / 2}, {y + robot_image.shape[0] / 2},")
                else:
                    log_file.write(f"{i}, {x + robot_image.shape[1] / 2}, {y + robot_image.shape[0] / 2},")

        # Log the end of the line for the current frame
        if log_output_path:
            log_file.write("\n")
        
        # Write the frame to the video file
        fig.canvas.draw()

        w, h = fig.canvas.get_width_height()
        buf = fig.canvas.buffer_rgba()
        frame = np.frombuffer(buf, dtype=np.uint8).reshape((h, w, 4))[:, :, :3].copy()


        # frame = np.frombuffer(fig.canvas.tostring_rgb(), dtype=np.uint8)
        # # get sure that the frame shape alligns with the video writer
        # frame = frame.reshape(fig.canvas.get_width_height()[::-1] + (3,))


        # repeat the writing of the frame to the video file for N_rep_frame
        N_rep_frame = 2
        for _ in range(N_rep_frame):
            writer.write(cv2.cvtColor(frame, cv2.COLOR_RGB2BGR))

    writer.release()
    plt.close(fig)


if __name__ == "__main__":
    import sys
    if len(sys.argv) == 1:
        # No CLI arguments: run the original demo code
        plt.rcParams['figure.dpi'] = 100

        robot_size = 56
        N = 5**2
        grid_size = (int(np.sqrt(N)), int(np.sqrt(N)))
        robot_str = 'Kilobot'
        date_str = datetime.now().strftime("%d%H%M%S")

        # Simple grid with circles
        experiment_name = f"grid_circle_N_{N}__{date_str}"
        generate_grid_image(grid_size=grid_size, circle_radius=robot_size/2, point_distance=100, image_size=(1000, 1000), output_path=f"etc/validation/media/{experiment_name}.png")
        print(f"Grid image generated and saved as '{experiment_name}.png'.")

        # Simple grid with robot images
        experiment_name = f"robot_grid_image_{robot_str}_N_{N}__{date_str}"
        generate_robot_grid_image(robot_image_path=f"etc/validation/{robot_str}.png", grid_size=grid_size, robot_width=robot_size, point_distance=100, image_size=(1000, 1000), output_path=f"etc/validation/media/{experiment_name}.png")
        print(f"Grid image generated and saved as '{experiment_name}.png'.")

        # Robot image with random robot images
        experiment_name = f"robot_image_with_random_robots_{robot_str}_N_{N}__{date_str}"
        generate_robot_image_with_random_robots(robot_image_path=f"etc/validation/{robot_str}.png", num_robots=N, robot_width=robot_size, image_size=(1000, 1000), output_path=f"etc/validation/media/{experiment_name}.png")
        print(f"Robot image with random robots generated and saved as '{experiment_name}.png'.")

        # Robot animation following a simple trajectory
        image_width = 1000
        star_points = [(image_width/2 + 300 * np.cos(theta), image_width/2 + 300 * np.sin(theta)) for theta in np.linspace(np.pi/2, 2 * np.pi + np.pi/2, 6)]
        order_index = [0, 2, 4, 1, 3, 0]
        trajectory = [star_points[i] for i in order_index]
        speed = 10
        experiment_name = f"robot_animation_star_traj_{robot_str}_Speed_{speed}"
        generate_robot_animation_simple_trajectory(robot_image_path="etc/validation/kilobot.png", trajectory=trajectory, robot_width=robot_size, image_size=(1000, 1000), robot_speed=speed, 
                                                   output_path=f"etc/validation/media/{experiment_name}.mp4", log_output_path=f"etc/validation/media/{experiment_name}_log.txt")
        print(f"Robot animation generated and saved as '{experiment_name}.mp4'.")

        # Robot animation with random robots
        N = 20
        date_str = datetime.now().strftime("%d%H%M%S")
        experiment_name = f"robot_animation_random_robots_{robot_str}_N_{N}"
        print(f"Experiment name: {experiment_name}")
        generate_robot_animation_random_robots(robot_image_path=f"etc/validation/{robot_str}.png", num_robots=N, robot_width=robot_size, image_size=(1000, 1000), robot_speed=3, animation_duration=2000, 
        output_path=f"etc/validation/media/{experiment_name}.mp4", log_output_path=f"etc/validation/media/{experiment_name}_log.txt")
    else:
        import argparse
        parser = argparse.ArgumentParser(description="Generate validation images and animations.")
        parser.add_argument('function', type=str, help='Function to call: grid, robot_grid, random_robots, robot_traj, robot_anim_random')
        parser.add_argument('--args', nargs='*', help='Arguments for the function (key=value pairs)', default=[])
        args = parser.parse_args()

        # Convert key=value pairs to kwargs
        kwargs = {}
        for arg in args.args:
            if '=' in arg:
                k, v = arg.split('=', 1)
                try:
                    v_eval = eval(v, {"__builtins__": None}, {})
                    kwargs[k] = v_eval
                except:
                    kwargs[k] = v
            else:
                kwargs[arg] = True

        if args.function == 'grid':
            generate_grid_image(**kwargs)
        elif args.function == 'robot_grid':
            generate_robot_grid_image(**kwargs)
        elif args.function == 'random_robots':
            generate_robot_image_with_random_robots(**kwargs)
        elif args.function == 'robot_traj':
            generate_robot_animation_simple_trajectory(**kwargs)
        elif args.function == 'robot_anim_random':
            generate_robot_animation_random_robots(**kwargs)
        else:
            print(f"Unknown function: {args.function}")
