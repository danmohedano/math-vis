import matplotlib.pyplot as plt
import numpy as np
from sympy import primerange


NUM_LIMIT = 100000000


def main():
    primes = list(primerange(NUM_LIMIT))
    n_primes = len(primes)
    diff = [0]
    changes = []
    for i, p in enumerate(primes):
        update = 1 if (p % 4) == 3 else -1
        diff.append(diff[-1] + update)
        if i > 2 and diff[-2] == 0 and diff[-3] * diff[-1] < 0:
            # Sign change
            changes.append(i)
    
    # Plot the difference
    plt.plot(list(range(n_primes + 1)), diff)

    # Plot the sign changing values
    for change_val in changes:
        plt.axvline(x=change_val, color='r', linestyle='dashed')
    
    plt.title(f"Prime race for {n_primes} primes generated")
    plt.xlabel("Prime number index")
    plt.grid()
    plt.ylabel(r"$| \{ p \equiv 3 mod 4 \} | - | \{ p \equiv 1 mod 4 \} |$")
    plt.show()


if __name__ == '__main__':
    main()