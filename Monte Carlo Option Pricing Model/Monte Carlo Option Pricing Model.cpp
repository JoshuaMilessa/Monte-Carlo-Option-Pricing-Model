#include <iostream>  // For input/output 
#include <cmath>  // For mathematical functions
#include <random>  // For random number generation
#include <vector>  // For storing stock paths
#include <fstream>  // For saving to CSV

// Simulate stock price paths
std::vector<std::vector<double>> simulateStockPaths(
    double S0, double r, double sigma, double T,
    int numSteps, int numPaths
) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    double dt = T / numSteps;
    std::vector<std::vector<double>> paths(numPaths, std::vector<double>(numSteps + 1));

    for (int i = 0; i < numPaths; i++) {
        paths[i][0] = S0;  // Start at S0
        for (int j = 1; j <= numSteps; j++) {
            double Z = dist(generator);
            paths[i][j] = paths[i][j - 1] *
                std::exp((r - 0.5 * sigma * sigma) * dt +
                    sigma * std::sqrt(dt) * Z);
        }
    }
    return paths;
}

// Monte Carlo pricing for a European Call Option
double monteCarloOptionPrice(double S0, double K, double r,
    double sigma, double T, int numSimulations) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    double totalPayoff = 0.0;

    for (int i = 0; i < numSimulations; ++i) {
        double Z = dist(generator);
        double ST = S0 * std::exp((r - 0.5 * sigma * sigma) * T +
            sigma * std::sqrt(T) * Z);
        double payoff = std::max(ST - K, 0.0);
        totalPayoff += payoff;
    }

    return std::exp(-r * T) * (totalPayoff / numSimulations);
}

int main() {
    double S0 = 100.0; // Current stock price
    double K = 100.0; // Strike price
    double r = 0.05; // Risk-free interest rate (5%)
    double sigma = 0.2; // Volatility (20%)
    double T = 1.0; // Time to maturity (1 year)
    int numSteps = 50; // Steps for path simulation
    int numPaths = 5; // Simulate 5 paths to visualize
    int numSimulations = 100000; // Simulations for pricing

    // Simulate stock price paths
    std::vector<std::vector<double>> paths =
        simulateStockPaths(S0, r, sigma, T, numSteps, numPaths);

    // Print a few paths to console
    std::cout << "Simulated Stock Price Paths:\n";
    for (int i = 0; i < numPaths; i++) {
        std::cout << "Path " << i + 1 << ": ";
        for (int j = 0; j <= numSteps; j++) {
            std::cout << paths[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Save paths to CSV
    std::ofstream file("stock_paths.csv");
    for (int j = 0; j <= numSteps; j++) {
        for (int i = 0; i < numPaths; i++) {
            file << paths[i][j];
            if (i < numPaths - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
    std::cout << "\nStock paths saved to 'stock_paths.csv'.\n";

    // Calculate the Monte Carlo option price 
    double optionPrice = monteCarloOptionPrice(S0, K, r, sigma, T, numSimulations);

// Built by AI help
    std::cout << "\n==============================" << std::endl;
    std::cout << " Monte Carlo Option Pricing" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "Stock Price (S0):      " << S0 << std::endl;
    std::cout << "Strike Price (K):      " << K << std::endl;
    std::cout << "Risk-Free Rate (r):    " << r << std::endl;
    std::cout << "Volatility (sigma):    " << sigma << std::endl;
    std::cout << "Time to Maturity (T):  " << T << " years" << std::endl;
    std::cout << "Simulations:           " << numSimulations << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Estimated Call Price:  $" << optionPrice << std::endl;
    std::cout << "==============================" << std::endl;

    return 0;
}
