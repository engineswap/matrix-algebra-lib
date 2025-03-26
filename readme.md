# Basic Matrix Library  
  ### Focused on Fast Matrix Multiplication (1 Non-SIMD Core Constraint)

  This project explores progressively faster algorithms for square matrix multiplication under the constraint of a single non-SIMD core. The improvements come entirely from better algorithmic design and cache efficiency.

  ---

  ## Naive Multiplication – 𝑂(n³)

  | Matrix Size            | Time Elapsed |
  |------------------------|--------------|
  | 32×32 × 32×32          |      0 ms    |
  | 128×128 × 128×128      |     27 ms    |
  | 256×256 × 256×256      |    222 ms    |
  | 512×512 × 512×512      |   1770 ms    |
  | 1024×1024 × 1024×1024   |  16887 ms    |

  ---

  ## Divide and Conquer – Still 𝑂(n³), But Faster

  Uses a recursive approach that applies naive multiplication at small sizes (block size = 64). This allows better use of cache:
  
  - Smaller matrices are more likely to fit in L1/L2/L3 cache.
  - Columns of `m2` are reused often and fetched from cache.
  - Conceptually similar to blocked/tiling approaches, with some overhead.
  
  | Matrix Size            | Time Elapsed |
  |------------------------|--------------|
  | 32×32 × 32×32          |      0 ms    |
  | 128×128 × 128×128      |     19 ms    |
  | 256×256 × 256×256      |    163 ms    |
  | 512×512 × 512×512      |   1293 ms    |
  | 1024×1024 × 1024×1024   |  10570 ms    |

  ---

  ## Strassen’s Algorithm – 𝑂(n^2.807)

  Strassen's method replaces some multiplications with additions, reducing the asymptotic complexity. This implementation:
  
  - Uses Strassen recursively.
  - Switches to naive multiplication at block size 64 for better locality and performance.
  
  | Matrix Size            | Time Elapsed |
  |------------------------|--------------|
  | 32×32 × 32×32          |      0 ms    |
  | 128×128 × 128×128      |      2 ms    |
  | 256×256 × 256×256      |     14 ms    |
  | 512×512 × 512×512      |     97 ms    |
  | 1024×1024 × 1024×1024   |    680 ms    |

  ---

  ## Summary

  We started with a 16-second naive algorithm for multiplying two 1024×1024 matrices and reduced it to under **700 milliseconds** by leveraging smarter recursion and cache-aware design — without touching parallelism or SIMD.

  ---
