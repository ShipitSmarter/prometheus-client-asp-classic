<%

' Write the metrics in the Prometheus Exposition Format
Sub prom_write_prom_exp_fmt(registry)
    Response.CodePage = 65001
    Response.Charset = "utf-8"
    Response.ContentType = "text/plain; version=0.0.4"

    Dim mfs, metrics
    metrics = registry.gather()
    For Each mfs In metrics
        Dim name: name = registry.prefix & mfs.Name

        ' Help line
        Response.Write "# HELP " & name & " "
        prom_write_prom_exp_fmt_escaped_help mfs.Help
        Response.Write vbLf

        ' Type line
        Response.Write "# TYPE " & name & " " & prom_get_prom_exp_fmt_type(mfs.MetricType) & vbLf

        ' Samples lines
        Dim smpl_curr
        For Each smpl_curr In mfs.Samples
            Response.Write registry.prefix & smpl_curr.Name
            If UBound(smpl_curr.LabelNames) >= 0 Then
                Response.Write "{"
                    Dim i, names, values
                    names = smpl_curr.LabelNames
                    values = smpl_curr.LabelValues
                    For i = 0 To UBound(smpl_curr.LabelNames)
                        Response.Write names(i) & "="""
                        prom_write_prom_exp_fmt_escaped_label values(i)
                        Response.Write ""","
                    Next
                Response.Write "}"
            End If
            Response.Write " " & smpl_curr.Value
            Response.Write vbLf
        Next

        Response.Write vbLf
    Next
End Sub

' Write the help description escaping the necessary characters.
Sub prom_write_prom_exp_fmt_escaped_help(help)
    Dim i
    For i = 1 To Len(help)
        Dim char : char = Mid(help, i, 1)
        If char = "\" Then
            Response.Write "\\"
        ElseIf char = vbCr Then
            ' Skip \r
        ElseIf char = vbLf Then
            Response.Write "\n"
        Else
            Response.Write char
        End If
    Next
End Sub

' Write a label value escaping the necessary characters.
Sub prom_write_prom_exp_fmt_escaped_label(label)
    Dim i
    For i = 1 To Len(label)
        Dim char : char = Mid(label, i, 1)
        If char = "\" Then
            Response.Write "\\"
        ElseIf char = """" Then
            Response.Write "\"""
        ElseIf char = vbCr Then
            ' Skip \r
        ElseIf char = vbLf Then
            Response.Write "\n"
        Else
            Response.Write char
        End If
    Next
End Sub

Function prom_get_prom_exp_fmt_type(mt_type)
    Select Case mt_type
        Case prom_MetricType_COUNTER
            prom_get_prom_exp_fmt_type = "counter"
        Case prom_MetricType_GAUGE
            prom_get_prom_exp_fmt_type = "gauge"
        Case Else
            prom_get_prom_exp_fmt_type = "untyped"
    End Select
End Function
%>