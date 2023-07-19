<%

Function prom_arrays_are_eqaul(arr_a, arr_b)
    If UBound(arr_a) <> UBound(arr_b) Then
        prom_arrays_are_eqaul = False
    Else
        Dim i
        For i = 0 To UBound(arr_a)
            If arr_a(i) <> arr_b(i) Then
                prom_arrays_are_eqaul = False
                Exit Function
            End If
        Next

        prom_arrays_are_eqaul = True
    End IF
End Function

%>