program NewtonRaphson
    ! Programa que utiliza o método de Newton Raphson para calcular raízes de uma função

    use, intrinsic :: iso_fortran_env, only: sp=>real32, dp=>real64
    implicit none

    real(dp) :: f, df, x, x0, lx, dx
    real(dp) :: eps
    integer :: i

    ! Pode ser substituido por qualquer função
    f(x)=-2*(16*exp(-x**2)*x**5-80*exp(-x**2)*x**3+60*exp(-x**2)*x)
    
    ! Derivada da função f(x) colocada acima
    df(x)=-2*(-32*exp(-x**2)*x**6+240*exp(-x**2)*x**4-360*exp(-x**2)*x**2+60*exp(-x**2))

    print *, 'Valor de x0: '
    read(*,*) x0

    eps = 0.0001_dp  ! Precisão
    dx = 1_dp        ! Valor inicial de dx
    x = x0           ! Valor inicial de x
    i = 1
    
    do while(dx.gt.eps)
        lx = x
        x = x - f(x)/df(x)
        dx = dabs(x-lx)

        print *, '|dx| =', dx
        print *, 'x = ', x,df(x),i

        i = i + 1 
    end do

    print *, 'Raiz encontrada: ', x
end
