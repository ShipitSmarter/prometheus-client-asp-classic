<%

' A metric and all of its samples.
Class prom_MetricFamilySamples
    Private m_type
    Public Property Get MetricType
        MetricType = m_type
    End Property

    Private m_name
    Public Property Get Name
        Name = m_name
    End Property

    Private m_help
    Public Property Get Help
        Help = m_help
    End Property

    Private m_samples
    Public Property Get Samples
        Samples = m_samples
    End Property

    Public Function Init(mt_type, name, help, samples)
        m_type = mt_type
        m_name = name
        m_help = help
        m_samples = samples
        Set Init = me
    End Function
End Class

' A single sample with a unique name and set of labels
Class prom_Sample
    Private m_name
    Public Property Get Name
        Name = m_name
    End Property

    Private m_label_names
    Public Property Get LabelNames
        LabelNames = m_label_names
    End Property
    
    Private m_label_values
    Public Property Get LabelValues
        LabelValues = m_label_values
    End Property

    Private m_dbl_value
    Public Property Get Value
        Value = m_dbl_value
    End Property

    Public Function Init(name, label_names, label_values, dbl_value)
        m_name = name
        m_label_names = label_names
        m_label_values = label_values
        m_dbl_value = dbl_value
        Set Init = me
    End Function
End Class

' MetricType Enum
Const prom_MetricType_COUNTER = 1
Const prom_MetricType_GAUGE = 2

%>