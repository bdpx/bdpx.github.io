
function docopen()
{
  document.writeln("<TABLE cellSpacing=0 cellPadding=0 width=\"100%\" border=0 vspace=0 hspace=0>");
//  document.writeln("<TBODY><TR>");
//  document.writeln("<TD width=199 height=105><A href=\"index.htm\"><IMG height=105 alt=\"Оглавление\" src=\"images/asterra.jpg\" width=199 border=0></A></TD>");
//  document.writeln("<TD vAlign=top width=\"100%\">");
//  document.writeln("<TABLE cellSpacing=0 cellPadding=0 width=\"100%\" border=0 vspace=0 hspace=0>");
//  document.writeln("<TBODY><TR><BR>");
//  document.writeln("<TD vAlign=top align=middle><FONT color=#aaaaaa size=1>УНИВЕРСИТЕТ<BR>КАФЕДРА</B></FONT> </TD></TR> <TR>");
  document.writeln("<TD vAlign=top align=middle><FONT color=#9933ff size=6><B>СИСТЕМНОЕ ПРОГРАММИРОВАНИЕ</B></FONT></TD></TR><TR>");
//  document.writeln("<BR>");
//  document.writeln("<TD vAlign=bottom align=right><FONT color=#ff0000 size=4><I>Студентам и преподавателям</I></FONT>");
  document.writeln("</TD></TR></TBODY></TABLE>");
//</TD></TR></TBODY></TABLE>

/*
  document.writeln("<TABLE cellSpacing=0 cellPadding=0 width=100% bgColor=#9933ff border=0 vspace=0 hspace=0>");
  document.writeln("<TBODY> <TR>");

  document.writeln("<TD align=middle>");
  document.writeln("<A href=\"index.htm\"><FONT color=#cccccc size=2>ГЛАВНАЯ</FONT></A>");
  document.writeln("<FONT color=#ffffff size=3>|</FONT>");

  document.writeln("<A href=\"news.htm\"><FONT color=#cccccc size=2>НОВОСТИ</FONT></A>");
  document.writeln("<FONT color=#ffffff size=3>|</FONT>");

  document.writeln("<A href=\"student.htm\"><FONT color=#cccccc size=2>УЧЕБНЫЕ МАТЕРИАЛЫ</FONT></A>");
  document.writeln("<FONT color=#ffffff size=3>|</FONT>");

  document.writeln("<A href=\"library.htm\"><FONT color=#ffffff size=2>ЧИТАЛЬНЫЙ ЗАЛ</FONT></A>");
  document.writeln("<FONT color=#ffffff size=3>|</FONT>");

  document.writeln("<A href=\"about.htm\"><FONT color=#cccccc size=2>АВТОР</FONT></A></TD></TR></TBODY></TABLE>");
*/
  document.writeln("<P align=center><A href=\"index.htm\">Вернуться к оглавлению</A><HR>");
}

function docclose(nextdoc)
{
  document.writeln("<HR><P>");
  document.writeln("<TABLE cellSpacing=0 width=\"100%\" bgColor=#9933ff border=0 vspace=0 hspace=0>");
  document.writeln("<TBODY><TR>");
  document.writeln("<TD align=left width=100><FONT color=#cccccc size=1><A href=\"index.htm\">BEGIN</A> </FONT></TD>");
  document.writeln("<TD align=left><FONT color=#ffffff size=2>");
  document.writeln("<MARQUEE delay=300 scroll>Системное программирование</MARQUEE></FONT></TD>");
  document.writeln("<TD align=right width=180><FONT color=#cccccc size=1>Последнее обновление: 12.02.2004</FONT></TD></TR></TBODY></TABLE></P>");
}


