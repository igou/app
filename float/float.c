double translate_nmea_deg_min_sec (double deg)
{
  int  intpart = (int)deg;
  double fracpart = deg - (double)intpart;

  if (fracpart < .0)
  {
    fracpart = -fracpart;
  }
  if (intpart < 0)
  {
    intpart = -intpart;
  }
  fracpart *= 60.0;

  return  ((double)(intpart) * 100.0) + fracpart;
}
