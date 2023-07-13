<%

Function arraysAreEqaul(arrA, arrB)
    If UBound(arrA) <> UBound(arrB) Then
        arraysAreEqaul = False
    Else
        Dim i
        For i = 0 To UBound(arrA)
            If arrA(i) <> arrB(i) Then
                arraysAreEqaul = False
                Exit For
            End If
        Next

        arraysAreEqaul = True
    End IF
End Function

%>