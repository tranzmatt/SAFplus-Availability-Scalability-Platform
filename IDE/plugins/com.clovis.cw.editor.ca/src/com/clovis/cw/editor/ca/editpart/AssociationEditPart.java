/*******************************************************************************
 * ModuleName  : com
 * $File: //depot/dev/main/Andromeda/IDE/plugins/com.clovis.cw.editor.ca/src/com/clovis/cw/editor/ca/editpart/AssociationEditPart.java $
 * $Author: bkpavan $
 * $Date: 2007/01/03 $
 *******************************************************************************/

/*******************************************************************************
 * Description :
 *******************************************************************************/

package com.clovis.cw.editor.ca.editpart;

import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.PolylineConnection;
import org.eclipse.draw2d.PolylineDecoration;

import com.clovis.cw.genericeditor.figures.AbstractConnectionFigure;

public class AssociationEditPart extends ProxyProxiedEditPart {

	/**
     * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
     */
    protected IFigure createFigure()
    {
        IFigure connectionFigure = new AbstractConnectionFigure(getConnectionModel());
       
        PolylineDecoration targetDecoration = new PolylineDecoration();
        ((PolylineConnection) connectionFigure).setTargetDecoration(
                targetDecoration);
        
        return connectionFigure;
    }
}