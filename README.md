# Monte Carlo Option Pricing (C++)

This project demonstrates how to **simulate stock prices** and **estimate the price of a European Call Option** using Monte Carlo simulation.

---

## What Does This Program Do?

This program estimates how much a European call option should cost **today** by simulating thousands of possible future stock prices.

1. **Simulates random future stock prices** based on how stocks move in the real world.  
2. **Checks the payoff** – for a call option, you only earn money if the stock price ends above the strike price.  
3. **Averages the payoffs** across all simulations.  
4. **Discounts the average back to today** using the risk-free interest rate.

The more simulations you run, the more accurate the estimate.

---

## The Math Behind Monte Carlo Option Pricing

Monte Carlo pricing works by simulating the expected payoff under **risk-neutral pricing**.

### **1. Stock Price Simulation**

We assume stock prices follow **Geometric Brownian Motion**:
\[
dS_t = r S_t \, dt + \sigma S_t \, dW_t
\]

Solving this gives:
\[
S_T = S_0 \times e^{(r - 0.5\sigma^2)T \;+\; \sigma \sqrt{T} Z}
\]

Where:
- \(S_0\) = stock price today  
- \(r\) = risk-free interest rate  
- \(\sigma\) = volatility  
- \(T\) = time to maturity (years)  
- \(Z \sim N(0,1)\) = standard normal random variable

---

### **2. Option Payoff**

- **Call Option:**  
  \[
  \text{Payoff} = \max(S_T - K, 0)
  \]

- **Put Option:** (future implementation)  
  \[
  \text{Payoff} = \max(K - S_T, 0)
  \]

---

### **3. Price Estimation**

The fair price today is the discounted average payoff:
\[
\text{Option Price} \approx e^{-rT} \times \frac{1}{N}\sum_{i=1}^N \text{Payoff}(S_T^{(i)})
\]

Where \(N\) is the number of simulations.

---

### **1. Compile the Program**

Using `g++`:

```bash
g++ src/main.cpp -o MonteCarloOptionPricing

r./MonteCarloOptionPricing

```
---

### Output View
<img width="277" height="244" alt="Output" src="https://github.com/user-attachments/assets/8d643ce6-4f25-4f87-9785-94f04b414926" />

---

Developed by Joshua Milessa
