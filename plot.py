import matplotlib.pyplot as plt

def plot_execution_time(input_sizes, execution_times1, execution_times2):
    plt.plot(input_sizes, execution_times1, marker='o', label='Merge-Sort')
    plt.plot(input_sizes, execution_times2, marker='o', label='Quick-Sort')
    plt.title('Execution Time vs Input Size')
    plt.xlabel('Input Size')
    plt.ylabel('Execution Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.show()

def main():
    # Example input sizes and corresponding execution times
    input_sizes = [10, 100, 500, 1000, 5000]
    execution_times1 = [0.000003, 0.000013, 0.000064, 0.000129, 0.000712]  # Replace with your actual execution times for the first data set
    execution_times2 = [3e-06, 1e-05,4.2e-05 ,  9.2e-05,  0.000558]  # Replace with your actual execution times for the second data set

    # Plot the results
    plot_execution_time(input_sizes, execution_times1, execution_times2)

if __name__ == "__main__":
    main()
