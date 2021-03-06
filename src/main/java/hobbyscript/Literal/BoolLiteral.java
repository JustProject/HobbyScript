package hobbyscript.Literal;

import hobbyscript.Ast.AstLeaf;
import hobbyscript.Eval.Env.EnvironmentCallBack;
import hobbyscript.Token.BoolToken;
import hobbyscript.Token.HobbyToken;

/**
 * BoolLiteral
 *
 * @author liufengkai
 *         Created by liufengkai on 16/7/27.
 */
public class BoolLiteral extends AstLeaf {

    public BoolLiteral(HobbyToken token) {
        super(token);
    }

    public int tag() {
        return token.getTag();
    }

    public boolean value() {
        return ((BoolToken) token).getType() == BoolToken.BoolType.TRUE;
    }

    @Override
    public Object eval(EnvironmentCallBack env) {
        if (value()) return Boolean.TRUE;
        return Boolean.FALSE;
    }
}
