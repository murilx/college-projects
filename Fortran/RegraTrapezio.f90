program FormulaTrapezio
    ! Programa que calcula a fórmula do trapézio, utilizada para calcular
    ! A área do gráfico de uma função

    use, intrinsic :: iso_fortran_env, only: sp=>real32, dp=>real64
    implicit none

    real(dp) :: f, x, xn
    real(dp) :: a, b, h
    real(dp) :: area, soma
    integer :: i, n

    ! Pode ser substituido por qualquer função
    f(x) = sqrt(1+(x**3))

    print *, 'Valor de a:'
    read(*,*) a
    print *, 'Valor de b:'
    read(*,*) b
    print *, 'Valor de n:'
    read(*,*) n

    xn = a
    h = (b-a)/n
    soma = 0.0_dp

    do i=1,n-1
        xn = xn + h
        soma = soma + f(xn)
        print *, i
    enddo

    area = (f(a) + f(b) + (2*soma))*(h/2)
    print *, 'Area =', area
end
