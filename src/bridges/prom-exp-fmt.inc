<%

' Write the metrics in the Prometheus Exposition Format
Sub writePromExpFmt(p_registry)
    Response.CodePage = 65001
    Response.Charset = "utf-8"
    Response.ContentType = "text/plain; version=0.0.4"

    Dim mfs, metrics
    metrics = p_registry.gather()
    For Each mfs In metrics
        Dim name: name = p_registry.Prefix & mfs.Name

        ' Help line
        Response.Write "# HELP " & name & " "
        writePromExpFmtEscapedHelp mfs.Help
        Response.Write vbLf

        ' Type line
        Response.Write "# TYPE " & name & " " & promExpFmtGetType(mfs.MetricType) & vbLf

        ' Samples lines
        Dim currSample
        For Each currSample In mfs.Samples
            Response.Write p_registry.Prefix & currSample.Name
            If UBound(currSample.LabelNames) >= 0 Then
                Response.Write "{"
                    Dim i, names, values
                    names = currSample.LabelNames
                    values = currSample.LabelValues
                    For i = 0 To UBound(currSample.LabelNames)
                        Response.Write names(i) & "="""
                        writePromExpFmtEscapedLabel values(i)
                        Response.Write ""","
                    Next
                Response.Write "}"
            End If
            Response.Write " " & currSample.Value
            Response.Write vbLf
        Next

        Response.Write vbLf
    Next
End Sub

' Write the help description escaping the necessary characters.
Sub writePromExpFmtEscapedHelp(p_help)
    Dim i
    For i = 1 To Len(p_help)
        Dim char : char = Mid(p_help, i, 1)
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
Sub writePromExpFmtEscapedLabel(p_label)
    Dim i
    For i = 1 To Len(p_label)
        Dim char : char = Mid(p_label, i, 1)
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

Function promExpFmtGetType(p_type)
    Select Case p_type
        Case MetricType_COUNTER
            promExpFmtGetType = "counter"
        Case MetricType_GAUGE
            promExpFmtGetType = "gauge"
        Case Else
            promExpFmtGetType = "untyped"
    End Select
End Function
%>