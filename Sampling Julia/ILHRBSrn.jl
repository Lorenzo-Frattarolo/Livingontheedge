function ILHRBS(n, k, T)

    U1 = rand(n, 1)
    kk = [1:k;]'
    K = repeat(kk, outer=[n, 1])
    #U=[U1 (K[:,2:end]-ones(n,k-1))/(k-1)-repeat(U1,outer = [1, k-1])/(k-1)];
    U = [U1 (K[:, 2:end] .- 1) / (k - 1) - repeat(U1, outer=[1, k - 1]) / (k - 1)]

    for j in (1:n)
        U[j, :] = U[j, shuffle(1:end)]
    end

    U = U[shuffle(1:end), :]
    KK = K
    i = 0
    while i < T
        i = i + 1
        for j in (1:n)
            KK[j, :] = K[j, shuffle(1:end)]
        end
        U = 1 / k * (KK .- 1 + U)
    end
    return U
end