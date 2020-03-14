
#define CALCULATE_ID 100


// input struct
struct Params
{
	float A, B, C, D;
	float alpa, betta, epsilon, gamma;
	int nodes;
	float delata;
};

fImage make_grafic(Params p)
{
	p.A = -3;
	p.B = 6;
	p.C = -5;
	p.D = 5;


	int width = 1600, height = 600 * 1.4f;
	fImage grafic(width, height);

	// extract some params
	int grafic_w = p.B - p.A;
	int grafic_h = p.D - p.C;
	//int grafic_w = 30;
	//int grafic_h = 4;

	float x_coef = float(grafic_w) / width ;
	float y_coef = height / float(grafic_h) / 2;

	// clear graph area
	draw_filled_rect(grafic, 0, 0, 1.0f, 1.0f, fColor(0));
	
	// draw axises
	if (p.A < 0 && p.B > 0)
		for (int y = 0; y < height; y++)
		{
			drawPixel(grafic, width * (float(abs(p.A) / grafic_w)), y, fColor(1.0f));
			drawPixel(grafic, width * (float(abs(p.A) / grafic_w)) + 1, y, fColor(1.0f));
		}

	// draw axises
	if (p.C < 0 && p.D > 0)
		for (int x = 0; x < width; x++)
		{
			drawPixel(grafic, x, height * (float(abs(p.C) / grafic_h)), fColor(1.0f));
			drawPixel(grafic, x, height * (float(abs(p.C) / grafic_h)) + 1, fColor(1.0f));
		}


	for (int x = 0; x < width-1; x++)
	{
		float y =  sinf(tanf(2) * x * x_coef) + cosf(x * x_coef);
		if (y < p.C || y > p.D) continue;
		y = y * y_coef + height / 2;

		for (int i = -2; i < 2; i++)
			for (int j = -3; j < 3; j++)                // kek smooth))))) wtf
				addPixel(grafic, x + i, y + j, fColor( min(1.0f, 9.0f / (1 + i*i +j*j)) ));
	}

	return grafic;
}


struct MainWindow : Window
{
	Label lExpression;
	Text tAlpha;
	Text tBetta;
	Text tEpsilon;
	Text tGamma;

	Label lA;
	Text  tA;
	Label lB;
	Text  tB;
	Label lC;
	Text  tC;
	Label lD;
	Text  tD;
	Label lNodes;
	Text  tNodes;
	Label lDelta;
	Text  tDelta;
	Button bCalculate;

	fImage grafic;
	Params params;

	MainWindow()
	{
		Params get_input(MainWindow * window);


		init(L"Stirling approximation", 800, 600, [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, Args args)->LRESULT
			{
				MainWindow* window = (MainWindow*)args[0];

				switch (msg)
				{
					case WM_COMMAND:
					{
						if (LOWORD(wParam) == CALCULATE_ID)
						{
							window->params = get_input(window);
							window->grafic = make_grafic(window->params);
							window->redraw();
						}
					}break;
					case WM_PAINT:
					{
						PAINTSTRUCT plug;
						BeginPaint(hwnd, &plug);

						draw_filled_rect(window->canvas, 0.0f, 0.7f, 1.0f, 1.0f, fColor(0.8f));
						draw_image(window->canvas, window->grafic, 0.0f, 0.0f, 1.0f, 0.7f);
						window->render_canvas();

						EndPaint(hwnd, &plug);
					}break;
					case WM_CLOSE:
					{
						quick_exit(0);
					}return 0;
				}

				return DefWindowProc(hwnd, msg, wParam, lParam);
			});

		UINT myStyle = WS_VISIBLE | WS_CHILD | WS_BORDER;

		lExpression.init(this->getHWND(), L"sin(tg(          x)) +           cos(          x)", 0, 0.1f, 0.02f, 0.53f, 0.06f, STATIC);
		tAlpha.init(this->getHWND(), 1, 0.03f, 0.02f, 0.07f, 0.06f, STATIC, myStyle);
		tBetta.init(this->getHWND(), 2, 0.2f, 0.02f, 0.07f, 0.06f, STATIC, myStyle);
		tEpsilon.init(this->getHWND(), 3, 0.35f, 0.02f, 0.07f, 0.06f, STATIC, myStyle);
		tGamma.init(this->getHWND(), 5, 0.51f, 0.02f, 0.07f, 0.06f, STATIC, myStyle);
		//
		//
		lA.init(this->getHWND(), L"A=", 0, 0.01f, 0.1f, 0.05f, 0.05f, STATIC);
		tA.init(this->getHWND(), 1, 0.05f, 0.1f, 0.07f, 0.05f, STATIC, myStyle);
		//
		lB.init(this->getHWND(), L"B=", 0, 0.01f, 0.15f, 0.05f, 0.05f, STATIC);
		tB.init(this->getHWND(), 1, 0.05f, 0.15f, 0.07f, 0.05f, STATIC, myStyle);
		//
		lC.init(this->getHWND(), L"C=", 0, 0.01f, 0.2f, 0.05f, 0.05f, STATIC);
		tC.init(this->getHWND(), 1, 0.05f, 0.2f, 0.07f, 0.05f, STATIC, myStyle);
		//
		lD.init(this->getHWND(),  L"D=", 0, 0.01f, 0.25f, 0.05f, 0.05f, STATIC);
		tD.init(this->getHWND(),  1, 0.05f, 0.25f, 0.07f, 0.05f, STATIC, myStyle);
		//
		lNodes.init(this->getHWND(), L"Nodes=", 0, 0.7f, 0.02f, 0.1f, 0.05f, STATIC);
		tNodes.init(this->getHWND(), 1, 0.8f, 0.02f, 0.07f, 0.05f, STATIC, myStyle);

		lDelta.init(this->getHWND(), L"Delta=", 0, 0.7f, 0.07f, 0.1f, 0.05f, STATIC);
		tDelta.init(this->getHWND(), 1, 0.8f, 0.07f, 0.11f, 0.05f, STATIC, myStyle);


		bCalculate.init(this->getHWND(), L"Calculate", CALCULATE_ID, 0.25f, 0.12f, 0.2f, 0.15f, STATIC);

		// set font size
		for (auto component : components[this->getHWND()])
			set_font_size(component.handle, 25);
		
		set_font_size(lExpression.handle, 30);
		set_min_max_size(800, 600);
	}
};


#define wtoi(str) ( str ? _wtoi(str) : 0)
#define wtof(str) ( str ? _wtof(str) : 0.0f)

Params get_input(MainWindow* window)
{
	Params p;

	p.A = wtof(window->tA.getText());
	p.B = wtof(window->tB.getText());
	p.C = wtof(window->tC.getText());
	p.D = wtof(window->tD.getText());

	p.alpa = wtof(window->tAlpha.getText());
	p.betta = wtof(window->tBetta.getText());
	p.epsilon= wtof(window->tEpsilon.getText());
	p.gamma= wtof(window->tGamma.getText());

	p.nodes = wtoi(window->tNodes.getText());
	p.delata= wtof(window->tDelta.getText());
	
	return p;
}