program FormulaSimpsonComposta
    ! Programa que utiliza a Formula de Simpson para calcular a área
    ! Do gráfico

    use, intrinsic :: iso_fortran_env, only: sp=>real32, dp=>real64
    implicit none

    real(dp) :: f, x, h
    real(dp) :: a, b, xn
    real(dp) :: area, soma
    real(dp) :: pi
    integer :: n, i

    ! Pode ser substituido por qualquer função
    f(x) = x*sin(x) 

    ! Aproximação de pi
    pi = 4.0_dp*datan(1.0_dp)

    print *, 'Valor de a:'
    read(*,*) a
    print *, 'Valor de b:'
    read(*,*) b
    print *, 'Valor de n:'
    read(*,*) n

    xn = a
    h = (b-a)/n
    soma = 0.0_dp

    do i=1, n-2
        xn = xn + h
        if (mod(i,2) .eq. 0) then
            soma = soma + 2*f(xn)
        else
            soma = soma + 4*f(xn)
        end if
    end do

    area = (soma + f(a) + f(b))*h/3
    print *, 'Area = ', area
end
