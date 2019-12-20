#sginclude "://shaders/commonlightmatdefs.inc"
#sginclude "://shaders/commonlightmodels.inc"

uniform float hasTexture=0.0f;
uniform sampler2D textureMap;
uniform float hasBump=0.0f;
uniform sampler2D bumpMap;

in vec3 viewPosition;
in vec3 viewNormal;
in vec2 texCoords;
out vec4 fragColor;

//Fuer das Verständnis der hier angewandten Berechnung des TBN-Systems sind folgende Quellen zu studieren:
//http://www.geeks3d.com/20130122/normal-mapping-without-precomputed-tangent-space-vectors/ [1]
//und als Verbesserung/follow-up:
//http://www.thetenthplanet.de/archives/1180 [2]
//Noch lesenswert: Eigentlich müsste die Inverse einer Matrix berechnet werden
//Die Inverse kann generell durch die adjugierte Matrix/det berechnet werden
//Unter http://www.emptyloop.com/technotes/A%20tutorial%20on%20inverting%203%20by%203%20matrices%20with%20cross%20products.pdf
//ist die Berechnung der adjugierten Matrix durch Kreuzprodukte dargestellt
//Daraus laesst sich (siehe [2]) dann die ug. Berechnung des contangent_frame ableiten

//Berechnet die Matrix, die den gestörten Normalenvektor aus dem TBN-Koordinantensystem ins WKS umrechnet!
mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv)
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );

    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

    // construct a scale-invariant frame
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

vec3 perturb_normal( vec3 N, vec3 V, vec2 texcoord )
{
    // assume N, the interpolated vertex normal and
    // V, the view vector (vertex to eye)
   vec3 map = texture(bumpMap, texcoord ).xyz;
   //siehe sign expansion in [2]
   //Nächste Zeile auskommentieren für VZ-behaftete Maps
   map = map * 255./127. - 128./127.;
   //Nächste Zeile auskommentieren für Maps, die schon mit 3 Kanälen kommen - selten!
   map.z = sqrt( 1. - dot( map.xy, map.xy ) );
   mat3 TBN = cotangent_frame(N, -V, texcoord);
   return normalize(TBN * map);
}

void main()
{
    vec3 perturbedViewNormal = perturb_normal(normalize(viewNormal), viewPosition, texCoords.xy);
    //PN ist jetzt in Weltkoordinaten, d.h. Eye, etc. müssen nicht umgerechnet werden!!!

    //Für die eigentliche Farbe gibt es mehrere Möglichkeiten
    //Man könnte _rein_ diejenige aus der Textur nehmen
    //Hier nehmen wir die aus dem Material und mischen dann ggf. mit der Textur
    //Dadurch kann das Aussehen des Objektes später noch durch das Material angepasst werden
    if (hasTexture > 0.5)
    {
        vec4 textureColor = texture(textureMap, texCoords);
        vec3 color = phong(viewPosition, -normalize(viewPosition), perturbedViewNormal, textureColor.rgb);
        fragColor = vec4(color, computeMaterialAlpha() * textureColor.a);
    }
    else
    {
        vec3 color = phong(viewPosition, -normalize(viewPosition), perturbedViewNormal, vec3(1.0));
        fragColor = vec4(color, computeMaterialAlpha());
    }

    fragColor.rgb += material.emission.rgb;
}
