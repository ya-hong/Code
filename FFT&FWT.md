$$
\newcommand {\DFT}[]{\mathrm{DFT}}
\newcommand {\trans}[]{\mathrm{trans}}
\newcommand {\or}[]{\mathrm{~or~}}
\newcommand {\and}[]{\mathrm{~and~}}
\newcommand {\xor}[]{\mathrm{~xor~}}
\newcommand {\cnt}[]{\mathrm{cnt}}
$$
# FFT 

对于 **FFT**, 有 $\DFT(A)_x \DFT(B)_x = \DFT(C)_x$:

$$
\begin{align*}
    DFT(A)_x = \sum_{i = 0} ^ {n - 1} \omega_n^{xi} A_i
\end{align*}
$$

$$
\begin{align*}
    & \sum_{i = 0} ^ {n - 1} \omega_n^{xi} A_i \sum_{j = 0} ^ {n - 1} \omega_n^{xj} B_j\\
    =& \sum_{k = 0} ^ {n - 1} \sum_{i + j \bmod n = k} \omega_n^{xi} \omega_n^{xj} A_i B_j\\
    =& \sum_{k = 0} ^ {n - 1}\sum_{i + j \bmod n = k} \omega_n^{xk} C_k
\end{align*}
$$

# FWT

令 $\trans(A)_x = \sum_{i = 0} ^ {n - 1} f(x, i) A_i$. 
只要能构造 $f$ 使得 $\trans(A)_x \trans(B)_x = \trans(C)_x$ 就能实现其他的变换. 

## 或卷积

需要满足当 $i \or j = k$ 时, $f(x, i) f(x, j) = f(x, k)$

$$
i \or x = x, j \or x = x \Rightarrow (i \or j) \or x = x\\
$$

$f(x, i) = [x \or i = x]$ 即可满足要求. 

## 与卷积

需要满足当 $i \and j = k$ 时, $f(x, i) f(x, j) = f(x, k)$

$$
i \and x = x, j \and x = x \Rightarrow (i \and j) \and x = x\\
$$

$f(x, i) = [x \and i = x]$. 

## 异或卷积

需要满足当 $i \xor j = k$ 时, $f(x, i) f(x, j) = f(x, k)$

令 $\cnt(x)$ 表示 $x$ 的二进制表示中的 $1$ 的个数. 
那么 $\cnt(i \and x) $ 的奇偶性异或 $\cnt(j \and x)$ 的奇偶性与 $\cnt((i \xor j) \and x)$ 的奇偶性相同.所以 $f(i, j) = -1 ^ (\cnt(i \and j))$

## 实现

按照二进制位分治, 每次只考虑 $0$, 和 $1$ 的情况. 
