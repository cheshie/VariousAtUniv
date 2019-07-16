using System;	
using System.Linq;
using System.Text;
using System.Collections.Generic;

namespace Rownanie_ns
{
	public class Rownanie
	{
		private List<int> m_dw{
			get {return m_dw; }
			set {m_dw = value; }
		}


		public Rownanie ()
		{
			m_dw = new int (4);

			foreach (int i in m_dw) {
				m_dw [i] = 0;
			}

		}

		static void wprowadz_dane()
		{
			foreach (int i in m_dw) {

				m_dw [i] = Console.ReadLine ();
			}

			return;
		}
	}
}

