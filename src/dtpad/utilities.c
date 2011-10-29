#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <Xm/Xm.h>
#include <Xm/XmAll.h>

Widget BxFindTopShell(Widget);
WidgetList BxWidgetIdsFromNames(Widget, char*, char*);

#include "utilities.h"

char *file_path_name = NULL;
size_t file_path_name_len = 0;
char *app_name = NULL;
Boolean backup_on_save = False;
Boolean been_saved = False;
Boolean file_dirty = False;

struct soft_break_lst {
	XmTextPosition pos;
	struct soft_break_lst *nxt;
};

struct soft_break_lst *soft_breaks = NULL;

void
add_soft_break(XmTextPosition value)
{
	struct soft_break_lst *breaks, *old; 
	
	if (NULL == soft_breaks) {
		soft_breaks = (struct soft_break_lst *)
		    XtMalloc(sizeof(struct soft_break_lst));
		soft_breaks->pos = value;
		soft_breaks->nxt = NULL;
		return;
	}
	
	breaks = soft_breaks;
	
	while (NULL != breaks) {
		if (value == breaks->pos)
			return;
		
		old = breaks;
		breaks = breaks->nxt;
	}
	
	breaks = old;
	breaks->nxt = (struct soft_break_lst *)
	    XtMalloc(sizeof(struct soft_break_lst));
	breaks->nxt->pos = value;
	breaks->nxt->nxt = NULL;
}

void
drop_soft_breaks(XmTextPosition start, XmTextPosition end)
{
	struct soft_break_lst *breaks, *nxt, *prev;
	XmTextPosition pos;
	
	breaks = soft_breaks;
	prev = NULL;
	
	while (NULL != breaks) {
		if (start <= breaks->pos <= end) {
			nxt = breaks->nxt;
			XtFree((char *) breaks);
			breaks = nxt;
			if (NULL != prev)
				prev->nxt = nxt;
		} else {
			prev = breaks;
			breaks = breaks->nxt;
		}
	}
}

Boolean
is_soft_break(XmTextPosition value)
{
	struct soft_break_lst *breaks;
	
	breaks = soft_breaks;
	
	while (NULL != breaks) {
		if (value == breaks->pos)
			return True;
		else
			breaks = breaks->nxt;
	}
	
	return False;
}

void
set_app_name(char *name)
{
	size_t len;
	char *buf;
	
	len = 1+strlen(name);
	buf = calloc(len, sizeof(char));
	
	if (NULL == buf) {
		perror("Dtpad (calloc)");
		exit(1);
	}
	
	strcpy(buf, name);
	if (app_name) XtFree(app_name);
	app_name = buf;
}

char *
get_app_name()
{
	return app_name;
}

void
manage_widget(Widget w, char *cb, char *name)
{
	WidgetList wlst;
	Widget widget;
	
	if (NULL == (wlst = BxWidgetIdsFromNames(w, cb, name))) { 
		fprintf(stderr, "Could not find %s widget.\n", name);
		perror("Error finding widget");
		exit(1);
	}
	
	widget = wlst[0];
	XtFree((char *)wlst);
	
	XtManageChild(widget);
}

Widget
get_widget_by_name(Widget w, char *cb, char *name)
{
	Widget widget;
	WidgetList wlst;
	
	if (NULL == (wlst = BxWidgetIdsFromNames(w, cb, name))) {
		fprintf(stderr, "Could not find %s widget.\n", name);
		exit(1);
	}
	
	widget = wlst[0];
	XtFree((char *)wlst);
	
	return widget;
}

long
str_linecount(char *s)
{
	long c;
	
	c = 0;	
	while (*(s++)) if ('\n' == *s) c++;
	
	return c;
}

char *
long_to_string(long n)
{
	int d;
	char *s;
	
	d = (int) 1+floor(log10(n));
		
	if (!(s = calloc(d+1, sizeof(char)))) {
		perror("Dtpad (long_to_string)");
		exit(1);
	}
	
	sprintf(s, "%d\0", n);
	
	return s;
}

void
update_message(Widget w, char *cb, char *msg)
{
	Widget widget;
	
	widget = get_widget_by_name(w, cb, "messageTextField");
	XmTextFieldSetString(widget, msg);
}

char *
get_file_contents(Widget w, char *cb, char *path)
{
	long file_size;
	char *file_data;
	FILE *file;
	
	if (NULL == (file = fopen(path, "r"))) {
		perror("Dtpad (fopen)");
		manage_widget(w, cb, "fileNotFoundMessageBox");
		return;
	}
	
	if (fseek(file, 0, SEEK_END)) {
		perror("Dtpad (fseek)");
		exit(1);
	}
	
	file_size = ftell(file);
	rewind(file);
	
	if (!(file_data = calloc(file_size, sizeof(char)))) {
		perror("Dtpad (calloc)");
		exit(1);
	}
	
	file_size = fread(file_data, sizeof(char), file_size, file);	
	file_data[file_size + 1] = '\0';
	
	if (fclose(file)) {
		perror("Dtpad (fclose)");
		exit(1);
	}

	return file_data;
}

void
update_window_title(Widget w, char *cb)
{
	char *path, *title, *name, *sep;
	int titlelen, namelen, seplen, pathlen;
	Widget top_w;
	
	top_w = get_widget_by_name(w, cb, "dtpad");
	
	name = get_app_name();
	namelen = strlen(name);

	sep = " - ";
	seplen = strlen(sep);
	
	path = get_save_path();
	if (NULL == path) path = "(Untitled)";
	pathlen = strlen(path);
	
	titlelen = 1+namelen+seplen+pathlen;
	title = calloc(titlelen, sizeof(char));
	
	if (NULL == title) {
		perror("Dtpad (calloc)");
		exit(1);
	}
	
	strcpy(title, name);
	strcat(title, sep);
	strcat(title, path);
		
	XtVaSetValues(top_w, XmNtitle, title, NULL);
	
	XtFree(title);
}

void
load_file(Widget w, char *cb, char *fname)
{
	char *data;
	Widget doc_w;
	
	data = get_file_contents(w, cb, fname);
	doc_w = get_document_text(w, cb);
	XmTextSetString(doc_w, data);
	
	update_document_linecount(w, cb);
	update_message(w, cb, "Loaded file.");
	set_save_path(fname);
	update_window_title(w, cb);
	
	XtFree(data);
}

void
update_document_linecount(Widget w, char *cb)
{
	int lines;
	char *lines_s;
	XmString label_s;
	Widget doc_w, line_lbl_w;
	
	doc_w = get_document_text(w, cb);
	line_lbl_w = get_widget_by_name(w, cb, "totalCountLabel");
	XtVaGetValues(doc_w, XmNtotalLines, &lines, NULL);
	lines_s = long_to_string(lines);
	label_s = XmStringCreateLocalized(lines_s);
	XtVaSetValues(line_lbl_w, XmNlabelString, label_s, NULL);
	
	XtFree(lines_s);
	XmStringFree(label_s);
}

void
set_save_path(char *path)
{
	size_t pathlen;
	
	if (NULL == path) {
		if (file_path_name) XtFree(file_path_name);
		file_path_name = NULL;
		file_path_name_len = 0;
		return;
	}
	
	pathlen = strlen(path);
	
	if (NULL == file_path_name || pathlen > file_path_name_len) 
		file_path_name = realloc(file_path_name, (1+pathlen)*sizeof(char));
	
	if (NULL == file_path_name) {
		perror("Dtpad (realloc)");
		exit(1);
	}
	
	strcpy(file_path_name, path);
	file_path_name_len = pathlen;
}

char *
get_save_path()
{
	return file_path_name;
}

void
backup_file(Widget w, char *cb)
{
	char *bak_path, *contents;
	size_t res;
	FILE *file, *bakf;
	long flen, bak_path_len;
	
	contents = NULL;
	bak_path = NULL;
	file = NULL;
	bakf = NULL;
	
	file = fopen(file_path_name, "r");
	
	if (NULL == file) {
		perror("Dtpad (fopen)");
		manage_widget(w, cb, "backupErrorMessageBox");
		goto Cleanup;
	}
	
	fseek(file, 0, SEEK_END);
	flen = ftell(file);
	rewind(file);
	
	bak_path_len = 2+strlen(file_path_name);
	bak_path = calloc(bak_path_len, sizeof(char));
	
	if (NULL == bak_path) {
		perror("Dtpad (calloc)");
		exit(1);
	}
	
	strcpy(bak_path, file_path_name);
	strcat(bak_path, "%");
	
	bakf = fopen(bak_path, "w");
	
	if (NULL == bakf) {
		perror("Dtpad (fopen)");
		manage_widget(w, cb, "backupErrorMessageBox");
		goto Cleanup;
	}
	
	contents = calloc(flen, sizeof(char));
	
	if (NULL == contents) {
		perror("Dtpad (calloc)");
		exit(1);
	}
	
	res = fread(contents, sizeof(char), flen, file);
	
	if (res != flen) {
		manage_widget(w, cb, "backupErrorMessageBox");
		goto Cleanup;
	}
	
	res = fwrite(contents, sizeof(char), flen, bakf);
	
	if (res != flen) {
		manage_widget(w, cb, "backupErrorMessageBox");
		goto Cleanup;
	}
	
Cleanup:

	if (NULL != file) fclose(file);
	if (NULL != bakf) fclose(bakf);
	free(bak_path);
	free(contents);
}

int
save_file(Widget w, char *cb)
{
	int code;
	size_t contents_size, written;
	char *contents;
	FILE *file;
	Widget widget;
	
	if (NULL == file_path_name) {
		fprintf(stderr, "No pathname was set; this should not happen.\n");
		exit(1);
	}
	
	if (True == backup_on_save && True == been_saved) 
		backup_file(w, cb);

	if (!(file = fopen(file_path_name, "w"))) {
		perror("Dtpad (fopen)");
		manage_widget(w, cb, "fileSaveFailedMessageBox");
		return EXIT_FAILURE;
	}
	
	widget = get_document_text(w, cb);
	contents = XmTextGetString(widget);
	contents_size = strlen(contents);
	written = fwrite(contents, sizeof(char), contents_size, file);
	
	if (written != contents_size) {
		perror("Dtpad (fwrite)");
		manage_widget(w, cb, "fileSaveTruncatedMessageBox");
		code = EXIT_FAILURE;
		goto cleanup;
	}
	
	update_message(w, cb, "File saved.");
	code = EXIT_SUCCESS;
	been_saved = True;
	
cleanup:
	XtFree(contents);
	
	if (fclose(file)) {
		perror("Dtpad (fclose)");
		exit(1);
	}
	
	return code;
}

Boolean
document_find(Widget w, char *cb, XEvent *event, char *msg)
{
	Boolean res;
	char *fstr;
	long flen;
	Time time;
	Widget doc_w, find_w;
	XAnyEvent *avent;
	XmTextPosition start, pos;
	
	doc_w = get_document_text(w, cb);
	find_w = get_widget_by_name(w, cb, "fdFindTextField");
	start = XmTextGetInsertionPosition(doc_w);
	fstr = XmTextFieldGetString(find_w);
	flen = strlen(fstr);
	avent = (XAnyEvent *) event;
	
	res = XmTextFindString(doc_w, start, fstr, XmTEXT_FORWARD, &pos);
	
	if (False == res)
		manage_widget(w, "findDlgCB", msg);
	else {
		time = XtLastTimestampProcessed(avent->display);
		XmTextSetSelection(doc_w, pos, pos+flen, time);
	}
	
	XtFree(fstr);
	return res;
}

void
document_change(Widget w, char *cb, XEvent *event)
{
	char *buf, *cstr, *fstr;
	long clen, flen;
	Widget doc_w, change_w, find_w;
	XmTextPosition left, right;
	
	doc_w = get_document_text(w, cb);
	find_w = get_widget_by_name(w, cb, "fdFindTextField");
	change_w = get_widget_by_name(w, cb, "fdChangeTextField");
	
	cstr = XmTextFieldGetString(change_w);
	fstr = XmTextFieldGetString(find_w);
	
	clen = strlen(cstr);
	flen = strlen(fstr);

Try:
	buf = XmTextGetSelection(doc_w);
	if (NULL == buf) {
		if (True == document_find(w, cb, event, "stringNotFoundMessageBox"))
			goto Try;
		else 
			goto Cleanup;
	} else if (!strcmp(fstr, buf)) {
		XmTextGetSelectionPosition(doc_w, &left, &right);
		XmTextReplace(doc_w, left, right, cstr);
	} else if (True == document_find(w, cb, event, "stringNotFoundMessageBox")) {
		XtFree(buf);
		goto Try;
	}

Cleanup:	
	XtFree(buf);
	XtFree(cstr);
	XtFree(fstr);
}

void 
document_changeall(Widget w, char *cb, XEvent *event)
{
	Widget doc_w;
	XmTextPosition pos;
	
	doc_w = get_document_text(w, cb);
	pos = XmTextGetInsertionPosition(doc_w);
	XmTextSetInsertionPosition(doc_w, 0);
	
	while (True == 
	    document_find(w, cb, event, "changeAllCompleteMessageBox"))
		document_change(w, cb, event);
		
	XmTextSetInsertionPosition(doc_w, pos);
}

void
set_backup_on_save(Boolean val)
{
	backup_on_save = val;
}

void
set_been_saved(Boolean val)
{
	been_saved = val;
}

void
set_file_dirty(Boolean val)
{
	file_dirty = val;
}

Boolean
isWrap(Widget w, char *cb)
{
	Widget tog_w;
	
	tog_w = get_widget_by_name(w, cb, "wrapToFitToggleButton");
	
	return XmToggleButtonGetState(tog_w);
}

Widget
get_document_text(Widget w, char *cb)
{
	char *name;

	if (True == isWrap(w, cb)) 
		name = "documentTextWrapped";
	else
		name = "documentText";
	
	return get_widget_by_name(w, cb, name);
}

XmTextPosition
line_to_position(char *buf, short line, short rows, short cols)
{
	short cur, col;
	XmTextPosition pos;

	if (rows < line) return rows;

	for (pos = 0, cur = 1, col = 0; cur < line; pos++, col++) {
		if ('\n' == buf[pos] || cols == col) {
			cur++;
			col = 0;
		}
	}

	return pos;
}

int
bw_next_line(char **buffer, size_t *brk, Dimension d, XmRenderTable rtbl)
{
	int res;
	char c;
	char *buf, *tmp;
	int count, old;
	Dimension width;
	XmString str;
	
	buf = *buffer;
	count = 0;
	
	while (*buf) {
		if ('\n' == *buf) {
			count++; buf++;
			break;
		} else {
			count++; buf++; 
		}
	}
	
	tmp = XtCalloc(count+1, sizeof(char));
	memcpy(tmp, *buffer, count);
	
	for (;;) {
		tmp[count] = '\0';
		str = XmStringCreateLocalized(tmp);
		width = XmStringWidth(rtbl, str);
		XmStringFree(str);

		if (width < d) {
			*buffer = buf;
			*brk += count;
			if (!(*buf)) { 
				res = 0; 
				break; 
			} else if ('\n' == buf[-1]) { 
				res = 1; 
				break; 
			} else { 
				res = 2; 
				break; 
			}
		}

		if (1 == count) {
			*buffer = buf;
			*brk += count;
			res = 2;
			break;
		}
		
		old = count;
		count = count * d / width;
		if (count == old) count--;
		buf -= (old - count) * sizeof(char);
	}
	
	XtFree(tmp);
	return res;
}

void
batch_wrap(Widget w, char *cb, 
    char *buffer, int *buffer_len, 
    XmTextPosition startPos)
{
	int i;
	char *buf, *tmp, *start;
	size_t brk, bufsize, tmpsize, xtra;
	Dimension cw, width, d;
	Position x, y;
	XmRenderTable rtbl;
	XmString cstr;
	
	brk = 0;
	buf = buffer;
	tmpsize = 1 + (bufsize = *buffer_len);
	tmp = XtCalloc(tmpsize, sizeof(char));
	start = tmp;
	memcpy(tmp, buf, bufsize);
	tmp[bufsize] = '\0';
	
	XmTextPosToXY(w, startPos, &x, &y);
	XtVaGetValues(w, 
	    XmNrenderTable, &rtbl, 
	    XmNwidth, &width,
	    NULL);
	    
	cstr = XmStringCreateLocalized("0");
	cw = XmStringWidth(rtbl, cstr);
	XmStringFree(cstr);
	
	for (xtra = 0, d = width - x; ; d = width - cw) {
		 switch (bw_next_line(&tmp, &brk, d, rtbl)) {
		 	case 0: /* No breaks found, done. */
				goto allfound;
			case 2: /* Soft break */
				add_soft_break(startPos+brk+xtra);
				xtra++;
			case 1: /* Hard break */
			default:
				break;
		}
	}
	
allfound: 
	bufsize += xtra;
	XtRealloc(buf, bufsize*sizeof(char));
	
	for (i = bufsize - 1; xtra > 0; i--) {
		if (is_soft_break(startPos+i)) {
			buf[i] = '\n';
			xtra--;
		} else {
			buf[i] = buf[i-xtra];
		}
	}
	
	*buffer_len = bufsize;
	XtFree(start);
}
