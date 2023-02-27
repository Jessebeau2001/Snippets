public class InstanceHoldingButton<T> : Button where T : Form, new()
{
	private IContainer components = null;
	private T? _instance = null;

	public InstanceHoldingButton()
	{
		InitializeComponent();
	}

	public InstanceHoldingButton(IContainer container)
	{
		container.Add(this);

		InitializeComponent();
	}

	private void InitializeComponent()
	{
		components = new System.ComponentModel.Container();
	}

	private void RemoveReference(object? sender, FormClosedEventArgs e)
	{
		if (_instance != null)
		{
			_instance.FormClosed -= RemoveReference;
			_instance = null;
		}
	}

	protected override void OnClick(EventArgs e)
	{
		base.OnClick(e);

		if (_instance == null)
		{
			_instance = new T();
			_instance.FormClosed += RemoveReference;
			_instance.Show();
		} else
		{
			_instance.Show();
			_instance.Focus();
		}
	}

	protected override void Dispose(bool disposing)
	{
		if (disposing && (components != null))
		{
			components.Dispose();
		}
		base.Dispose(disposing);
	}
}
